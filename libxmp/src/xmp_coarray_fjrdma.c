#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>
#include <string.h>
#include "mpi.h"
#include "mpi-ext.h"
#include "xmp_internal.h"
#define FJRDMA_MAX_SIZE 16777212
#define FJRDMA_MAX_MEMID 511
#define FJRDMA_MAX_MPUT 1993
#define FJRDMA_MAX_MGET 100 /** This value is a trial */
#define FJRDMA_TAG 0
#define FJRDMA_START_MEMID 2
extern void _XMP_set_coarray_addresses(const uint64_t, const _XMP_array_section_t*, const int, const size_t, uint64_t*);

static int _num_of_puts = 0;
static struct FJMPI_Rdma_cq _cq;
static int _memid = FJRDMA_START_MEMID; // _memid = 0 (macro MEMID in xmp_internal.h) is used to put/get operations.
                                        // _memid = 1 (macro POST_WAID_ID in xmp_internal.h) is used to post/wait operations.

void _XMP_fjrdma_malloc_do(_XMP_coarray_t *coarray, void **buf, const size_t coarray_size)
{
  uint64_t *each_addr = _XMP_alloc(sizeof(uint64_t) * _XMP_world_size);
  if(_memid == FJRDMA_MAX_MEMID)
    _XMP_fatal("Too many coarrays. Number of coarrays is not more than 510.");

  *buf = _XMP_alloc(coarray_size);
  uint64_t laddr = FJMPI_Rdma_reg_mem(_memid, *buf, coarray_size);

  MPI_Barrier(MPI_COMM_WORLD);
  for(int ncount=0,i=1; i<_XMP_world_size+1; ncount++,i++){
    int partner_rank = (_XMP_world_rank + _XMP_world_size - i) % _XMP_world_size;
    if(partner_rank == _XMP_world_rank)
      each_addr[partner_rank] = laddr;
    else
      each_addr[partner_rank] = FJMPI_Rdma_get_remote_addr(partner_rank, _memid);

    if(ncount > 3000){
      MPI_Barrier(MPI_COMM_WORLD);
      ncount = 0;
    }
  }

  coarray->real_addr = *buf;
  coarray->addr = (void *)each_addr;
  _memid++;
}

void _XMP_fjrdma_coarray_lastly_deallocate()
{
  if(_memid == FJRDMA_START_MEMID) return;

  _memid--;
  FJMPI_Rdma_dereg_mem(_memid);
}

void _XMP_fjrdma_shortcut_put(const int target_image, const uint64_t dst_point, const uint64_t src_point,
			      const _XMP_coarray_t *dst_desc, const _XMP_coarray_t *src_desc, const size_t transfer_size)
{
  if(transfer_size > FJRDMA_MAX_SIZE){
    fprintf(stderr, "transfer_size is too large %zu\n", transfer_size);
    exit(1);
  }

  uint64_t raddr = (uint64_t)dst_desc->addr[target_image] + dst_point;
  uint64_t laddr = (uint64_t)src_desc->addr[_XMP_world_rank] + src_point;

  FJMPI_Rdma_put(target_image, FJRDMA_TAG, raddr, laddr, transfer_size, FLAG_NIC);
  _num_of_puts++;
}

// Both src and dst arrays are continuous.
static void _fjrdma_continuous_put(const int target_image, const uint64_t dst_point, const uint64_t src_point,
				   const _XMP_coarray_t *dst_desc, const _XMP_coarray_t *src_desc,
				   const void *src, const size_t transfer_size)
/* If a local array is a coarray, src_desc != NULL. */
{
  uint64_t raddr = (uint64_t)dst_desc->addr[target_image] + dst_point;
  uint64_t laddr;

  if(src_desc == NULL)
    laddr = FJMPI_Rdma_reg_mem(_XMP_TEMP_MEMID, (void *)((char *)src+src_point), transfer_size);
  else
    laddr = (uint64_t)src_desc->addr[_XMP_world_rank] + src_point;

  _num_of_puts++;
  FJMPI_Rdma_put(target_image, FJRDMA_TAG, raddr, laddr, transfer_size, FLAG_NIC);

  if(src_desc == NULL)   
    FJMPI_Rdma_dereg_mem(_XMP_TEMP_MEMID);
}

// Number of elements of src must be 1, number of elements of dst must be more than 1.
// e.g. a[0:100:3]:[2] = b;
static void _fjrdma_scalar_mput(const int target_image, const uint64_t dst_point, const uint64_t src_point, 
				const _XMP_array_section_t *dst_info, const int dst_dims,
				const _XMP_coarray_t *dst_desc, const _XMP_coarray_t *src_desc, 
				const void *src, const size_t transfer_coarray_elmts)
/* If a local array is a coarray, src_desc != NULL. */
{
  uint64_t raddr = (uint64_t)dst_desc->addr[target_image] + dst_point;
  uint64_t laddr;
  size_t elmt_size = dst_desc->elmt_size;
  uint64_t raddrs[transfer_coarray_elmts], laddrs[transfer_coarray_elmts];
  size_t lengths[transfer_coarray_elmts];

  if(src_desc == NULL)
    laddr = FJMPI_Rdma_reg_mem(_XMP_TEMP_MEMID, (void *)((char *)src+src_point), elmt_size);
  else
    laddr = (uint64_t)src_desc->addr[_XMP_world_rank] + src_point;

  // Set parameters for FJMPI_Rdma_mput
  _XMP_set_coarray_addresses(raddr, dst_info, dst_dims, transfer_coarray_elmts, raddrs);
  for(int i=0;i<transfer_coarray_elmts;i++) laddrs[i] = laddr;
  for(int i=0;i<transfer_coarray_elmts;i++) lengths[i] = elmt_size;

  if(transfer_coarray_elmts <= FJRDMA_MAX_MPUT){
    FJMPI_Rdma_mput(target_image, FJRDMA_TAG, raddrs, laddrs, lengths, 0, transfer_coarray_elmts, FLAG_NIC);
    _num_of_puts++;
  }
  else{
    int times      = transfer_coarray_elmts / FJRDMA_MAX_MPUT + 1;
    int rest_elmts = transfer_coarray_elmts - FJRDMA_MAX_MPUT * (times - 1);

    for(int i=0;i<times;i++){
      size_t trans_elmts = (i != times-1)? FJRDMA_MAX_MPUT : rest_elmts;
      FJMPI_Rdma_mput(target_image, FJRDMA_TAG, &raddrs[i*FJRDMA_MAX_MPUT], &laddrs[i*FJRDMA_MAX_MPUT], 
		      &lengths[i*FJRDMA_MAX_MPUT], 0, trans_elmts, FLAG_NIC);
    }
    _num_of_puts += times;
  }

  if(src_desc == NULL)
    FJMPI_Rdma_dereg_mem(_XMP_TEMP_MEMID);
}

static size_t _get_array_size(const _XMP_array_section_t *array, int dims)
{
  return array[0].distance * array[dims-1].elmts;
}


static void _fjrdma_NON_continuous_put_1dim_same_stride(const int target_image, uint64_t raddr, uint64_t laddr,
							const size_t transfer_coarray_elmts, const int stride, size_t elmt_size)
{
  /** e.g. a[0:10:2]:[2] = b[2:10:2];
      In this pattern, the sixth argument of FJMPI_Rdma_mput() can NOT be 0.
  */
  if(transfer_coarray_elmts <= FJRDMA_MAX_MPUT){
    FJMPI_Rdma_mput(target_image, FJRDMA_TAG, &raddr, &laddr,
		    &elmt_size, stride, transfer_coarray_elmts, FLAG_NIC);
    _num_of_puts++;
  }
  else{
    int times      = transfer_coarray_elmts / FJRDMA_MAX_MPUT + 1;
    int rest_elmts = transfer_coarray_elmts - FJRDMA_MAX_MPUT * (times - 1);
    for(int i=0;i<times;i++){
      uint64_t tmp_raddr = raddr + (i*FJRDMA_MAX_MPUT*stride);
      uint64_t tmp_laddr = laddr + (i*FJRDMA_MAX_MPUT*stride);
      size_t trans_elmts = (i != times-1)? FJRDMA_MAX_MPUT : rest_elmts;
      FJMPI_Rdma_mput(target_image, FJRDMA_TAG, &tmp_raddr, &tmp_laddr,
		      &elmt_size, stride, trans_elmts, FLAG_NIC);
    }
    _num_of_puts += times;
  }
}

static void _fjrdma_NON_continuous_put_general(const int target_image, uint64_t raddr, uint64_t laddr,
					       const size_t transfer_coarray_elmts,
					       const _XMP_array_section_t *dst_info, const _XMP_array_section_t *src_info,
					       const int dst_dims, const int src_dims, size_t elmt_size)
{
  uint64_t raddrs[transfer_coarray_elmts], laddrs[transfer_coarray_elmts];
  size_t   lengths[transfer_coarray_elmts];

  // Set parameters for FJMPI_Rdma_mput
  _XMP_set_coarray_addresses(raddr, dst_info, dst_dims, transfer_coarray_elmts, raddrs);
  _XMP_set_coarray_addresses(laddr, src_info, src_dims, transfer_coarray_elmts, laddrs);
  for(int i=0;i<transfer_coarray_elmts;i++) lengths[i] = elmt_size;

  if(transfer_coarray_elmts <= FJRDMA_MAX_MPUT){
    FJMPI_Rdma_mput(target_image, FJRDMA_TAG, raddrs, laddrs, lengths, 0, transfer_coarray_elmts, FLAG_NIC);
    _num_of_puts++;
  }
  else{
    int times      = transfer_coarray_elmts / FJRDMA_MAX_MPUT + 1;
    int rest_elmts = transfer_coarray_elmts - FJRDMA_MAX_MPUT * (times - 1);
    
    for(int i=0;i<times;i++){
      size_t trans_elmts = (i != times-1)? FJRDMA_MAX_MPUT : rest_elmts;
      FJMPI_Rdma_mput(target_image, FJRDMA_TAG, &raddrs[i*FJRDMA_MAX_MPUT], &laddrs[i*FJRDMA_MAX_MPUT],
		      &lengths[i*FJRDMA_MAX_MPUT], 0, trans_elmts, FLAG_NIC);
    }
    _num_of_puts += times;
  }
}
// src and/or dst arrays are NOT continuous.
static void _fjrdma_NON_continuous_put(const int target_image, const uint64_t dst_point, const uint64_t src_point,
				       const _XMP_array_section_t *dst_info, const _XMP_array_section_t *src_info,
				       const int dst_dims, const int src_dims, 
				       const _XMP_coarray_t *dst_desc, const _XMP_coarray_t *src_desc, 
				       void *src, const size_t transfer_coarray_elmts)
/* If a local array is a coarray, src_desc != NULL. */
{
  uint64_t raddr = (uint64_t)dst_desc->addr[target_image] + dst_point;
  uint64_t laddr;
  size_t elmt_size = dst_desc->elmt_size;

  if(src_desc == NULL){
    size_t array_size = _get_array_size(src_info, src_dims);
    laddr = FJMPI_Rdma_reg_mem(_XMP_TEMP_MEMID, src, array_size) + src_point;
  }
  else{
    laddr = (uint64_t)src_desc->addr[_XMP_world_rank] + src_point;
  }

  if(dst_dims == 1 && src_dims == 1 && dst_info[0].stride == src_info[0].stride){
    _fjrdma_NON_continuous_put_1dim_same_stride(target_image, raddr, laddr, transfer_coarray_elmts,
						dst_info[0].stride*elmt_size, elmt_size);
  }
  else{
    _fjrdma_NON_continuous_put_general(target_image, raddr, laddr, transfer_coarray_elmts, 
				       dst_info, src_info, dst_dims, src_dims, elmt_size);
  }

  if(src_desc == NULL)
    FJMPI_Rdma_dereg_mem(_XMP_TEMP_MEMID);
}

void _XMP_fjrdma_put(const int dst_continuous, const int src_continuous, const int target_image, const int dst_dims, const int src_dims, 
		     const _XMP_array_section_t *dst_info, const _XMP_array_section_t *src_info, const _XMP_coarray_t *dst_desc, 
		     void *src, const _XMP_coarray_t *src_desc, const int transfer_coarray_elmts, const int transfer_array_elmts)
{
  uint64_t dst_point = (uint64_t)_XMP_get_offset(dst_info, dst_dims);
  uint64_t src_point = (uint64_t)_XMP_get_offset(src_info, src_dims);

  if(transfer_coarray_elmts == transfer_array_elmts){
    size_t transfer_size = dst_desc->elmt_size * transfer_coarray_elmts;
    if(transfer_size > FJRDMA_MAX_SIZE){
      fprintf(stderr, "transfer_size is too large %zu\n", transfer_size);
      exit(1);
    }

    if(dst_continuous == _XMP_N_INT_TRUE && src_continuous == _XMP_N_INT_TRUE){
      _fjrdma_continuous_put(target_image, dst_point, src_point, dst_desc, src_desc, src, transfer_size);
    }
    else{
      _fjrdma_NON_continuous_put(target_image, dst_point, src_point, dst_info, src_info, dst_dims, src_dims, dst_desc, src_desc, 
				 src, transfer_coarray_elmts);
    }
  }
  else{
    if(transfer_array_elmts == 1){
      _fjrdma_scalar_mput(target_image, dst_point, src_point, dst_info, dst_dims, dst_desc, src_desc, src, transfer_coarray_elmts);
    }
    else{
      _XMP_fatal("Number of elements is invalid");
    }
  }
}

void _XMP_fjrdma_shortcut_get(const int target_image, const uint64_t dst_point, const uint64_t src_point,
			      const _XMP_coarray_t *dst_desc, const _XMP_coarray_t *src_desc,
			      const size_t transfer_size)
{
  if(transfer_size > FJRDMA_MAX_SIZE){
    fprintf(stderr, "transfer_size is too large %d\n", transfer_size);
    exit(1);
  }

  uint64_t raddr = (uint64_t)src_desc->addr[target_image] + src_point;
  uint64_t laddr = (uint64_t)dst_desc->addr[_XMP_world_rank] + dst_point;
  
  // To complete put operations before the following get operation.
  _XMP_fjrdma_sync_memory();
  FJMPI_Rdma_get(target_image, FJRDMA_TAG, raddr, laddr, transfer_size, FLAG_NIC);

  // To complete the above get operation.
  while(FJMPI_Rdma_poll_cq(SEND_NIC, &_cq) != FJMPI_RDMA_NOTICE);
}

static void _fjrdma_continuous_get(const int target_image, const uint64_t dst_point, const uint64_t src_point,
				   const void *dst, const _XMP_coarray_t *dst_desc, const _XMP_coarray_t *src_desc, 
				   const size_t transfer_size)
/* If a local array is a coarray, dst_desc != NULL. */
{
  uint64_t raddr = (uint64_t)src_desc->addr[target_image] + src_point;
  uint64_t laddr;

  if(dst_desc == NULL)
    laddr = FJMPI_Rdma_reg_mem(_XMP_TEMP_MEMID, (void *)((char *)dst+dst_point), transfer_size);
  else
    laddr = (uint64_t)dst_desc->addr[_XMP_world_rank] + dst_point;
  
  // To complete put operations before the following get operation.
  _XMP_fjrdma_sync_memory();

  FJMPI_Rdma_get(target_image, FJRDMA_TAG, raddr, laddr, transfer_size, FLAG_NIC);

  // To complete the above get operation.
  while(FJMPI_Rdma_poll_cq(SEND_NIC, &_cq) != FJMPI_RDMA_NOTICE);

  if(dst_desc == NULL)
    FJMPI_Rdma_dereg_mem(_XMP_TEMP_MEMID);
}

static void _fjrdma_NON_continuous_get(const int target_image, const uint64_t dst_point, const uint64_t src_point,
				       const _XMP_array_section_t *dst_info, const _XMP_array_section_t *src_info,
				       void *dst, const _XMP_coarray_t *dst_desc, const _XMP_coarray_t *src_desc,
				       const int dst_dims, const int src_dims, const int transfer_coarray_elmts)
/* If a local array is a coarray, dst_desc != NULL. */
{
  uint64_t raddr = (uint64_t)src_desc->addr[target_image] + src_point;
  uint64_t laddr;
  uint64_t raddrs[transfer_coarray_elmts], laddrs[transfer_coarray_elmts];
  size_t elmt_size = src_desc->elmt_size;

  if(dst_desc == NULL){
    size_t array_size = _get_array_size(dst_info, dst_dims);
    laddr = FJMPI_Rdma_reg_mem(_XMP_TEMP_MEMID, dst, array_size) + dst_point;
  }
  else{
    laddr = (uint64_t)dst_desc->addr[_XMP_world_rank] + dst_point;
  }

  // Set parameters for multipul FJMPI_Rdma_get()
  _XMP_set_coarray_addresses(laddr, dst_info, dst_dims, transfer_coarray_elmts, laddrs);
  _XMP_set_coarray_addresses(raddr, src_info, src_dims, transfer_coarray_elmts, raddrs);

  // To complete put operations before the following get operation.
  _XMP_fjrdma_sync_memory();

  if(transfer_coarray_elmts <= FJRDMA_MAX_MGET){
    for(int i=0;i<transfer_coarray_elmts;i++)
      FJMPI_Rdma_get(target_image, FJRDMA_TAG, raddrs[i], laddrs[i], elmt_size, FLAG_NIC);

    // To complete the above get operation.
    for(int i=0;i<transfer_coarray_elmts;i++)
      while(FJMPI_Rdma_poll_cq(SEND_NIC, &_cq) != FJMPI_RDMA_NOTICE);
  }
  else{
    int times      = transfer_coarray_elmts / FJRDMA_MAX_MGET + 1;
    int rest_elmts = transfer_coarray_elmts - FJRDMA_MAX_MGET * (times - 1);

    for(int i=0;i<times;i++){
      size_t trans_elmts = (i != times-1)? FJRDMA_MAX_MGET : rest_elmts;
      for(int j=0;j<trans_elmts;j++)
	FJMPI_Rdma_get(target_image, FJRDMA_TAG, raddrs[j+i*FJRDMA_MAX_MGET], laddrs[j+i*FJRDMA_MAX_MGET], 
		       elmt_size, FLAG_NIC);

      // To complete the above get operation.
      for(int i=0;i<trans_elmts;i++)
	while(FJMPI_Rdma_poll_cq(SEND_NIC, &_cq) != FJMPI_RDMA_NOTICE);
    }
  }

  if(dst_desc == NULL)
    FJMPI_Rdma_dereg_mem(_XMP_TEMP_MEMID);
}

void _XMP_fjrdma_get(const int src_continuous, const int dst_continuous, const int target_image, const int src_dims, const int dst_dims, 
		     const _XMP_array_section_t *src_info, const _XMP_array_section_t *dst_info, const _XMP_coarray_t *src_desc, 
		     void *dst, const _XMP_coarray_t *dst_desc, const int transfer_coarray_elmts, const int transfer_array_elmts)
{
  if(transfer_coarray_elmts == transfer_array_elmts){
    size_t transfer_size = src_desc->elmt_size * transfer_coarray_elmts;

    if(transfer_size > FJRDMA_MAX_SIZE){
      fprintf(stderr, "transfer_size is too large %zu\n", transfer_size);
      exit(1);
    }
  
    uint64_t dst_point = (uint64_t)_XMP_get_offset(dst_info, dst_dims);
    uint64_t src_point = (uint64_t)_XMP_get_offset(src_info, src_dims);
    if(dst_continuous == _XMP_N_INT_TRUE && src_continuous == _XMP_N_INT_TRUE){
      _fjrdma_continuous_get(target_image, dst_point, src_point, dst, dst_desc, src_desc, transfer_size);
    }
    else{
      _fjrdma_NON_continuous_get(target_image, dst_point, src_point, dst_info, src_info,
				 dst, dst_desc, src_desc, dst_dims, src_dims, transfer_coarray_elmts);
    }
  }
  else{
    _XMP_fatal("Number of elements is invalid");
  }
}

void _XMP_fjrdma_sync_memory()
{
  while(_num_of_puts != 0){
    if(FJMPI_Rdma_poll_cq(SEND_NIC, &_cq) == FJMPI_RDMA_NOTICE)
      _num_of_puts--;
  }
}

void _XMP_fjrdma_sync_all()
{
  _XMP_fjrdma_sync_memory();
  MPI_Barrier(MPI_COMM_WORLD);
}