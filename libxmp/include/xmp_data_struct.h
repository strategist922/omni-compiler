/*
 * $TSUKUBA_Release: $
 * $TSUKUBA_Copyright:
 *  $
 */

#ifndef _XMP_DATA_STRUCT
#define _XMP_DATA_STRUCT

#include <stdbool.h>
#include "xmp_constant.h"

#define _XMP_comm void

// nodes descriptor
typedef struct _XMP_nodes_info_type {
  int size;

  // enable when is_member is true
  int rank;
  // -----------------------------
} _XMP_nodes_info_t;

typedef struct _XMP_nodes_type {
  _Bool is_member;
  int dim;
  int comm_size;

  // enable when is_member is true
  int comm_rank;
  _XMP_comm *comm;
  // -----------------------------

  _XMP_nodes_info_t info[1];
} _XMP_nodes_t;

// template desciptor
typedef struct _XMP_template_info_type {
  // enable when is_fixed is true
  long long ser_lower;
  long long ser_upper;
  unsigned long long ser_size;
  // ----------------------------
} _XMP_template_info_t;

typedef struct _XMP_template_chunk_type {
  // enable when is_owner is true
  long long par_lower;
  long long par_upper;
  // ----------------------------

  int par_stride;
  unsigned long long par_chunk_width;
  int dist_manner;
  _Bool is_regular_chunk;

  // enable when dist_manner is not _XMP_N_DIST_DUPLICATION
  int onto_nodes_index;
  _XMP_nodes_info_t *onto_nodes_info;
  // ------------------------------------------------------
} _XMP_template_chunk_t;

typedef struct _XMP_template_type {
  _Bool is_fixed;
   _Bool is_distributed;
    _Bool is_owner;

  int   dim;

  // enable when is_distributed is true
  _XMP_nodes_t *onto_nodes;
  _XMP_template_chunk_t *chunk;
  // ----------------------------------

  _XMP_template_info_t info[1];
} _XMP_template_t;

// aligned array descriptor
typedef struct _XMP_array_info_type {
  _Bool is_shadow_comm_member;
  _Bool is_regular_chunk;
  int align_manner;

  int ser_lower;
  int ser_upper;
  int ser_size;

  // enable when is_allocated is true
  int par_lower;
  int par_upper;
  int par_stride;
  int par_size;

  int local_lower;
  int local_upper;
  int local_stride;
  int alloc_size;

  int *temp0;
  int temp0_v;

  unsigned long long dim_acc;
  unsigned long long dim_elmts;
  // --------------------------------

  long long align_subscript;

  int shadow_type;
  int shadow_size_lo;
  int shadow_size_hi;

  // enable when is_shadow_comm_member is true
  _XMP_comm *shadow_comm;
  int shadow_comm_size;
  int shadow_comm_rank;
  // -----------------------------------------

  // align_manner is not _XMP_N_ALIGN_NOT_ALIGNED
  int align_template_index;
  _XMP_template_info_t *align_template_info;
  _XMP_template_chunk_t *align_template_chunk;
  // --------------------------------------------
} _XMP_array_info_t;

typedef struct _XMP_array_type {
  _Bool is_allocated;
  _Bool is_align_comm_member;
  int dim;
  int type;
  size_t type_size;

  // enable when is_allocated is true
  unsigned long long total_elmts;
  // --------------------------------

  // enable when is_align_comm_member is true
  _XMP_comm *align_comm;
  int align_comm_size;
  int align_comm_rank;
  // ----------------------------------------

  _XMP_template_t *align_template;
  _XMP_array_info_t info[1];
} _XMP_array_t;

typedef struct _XMP_task_desc_type {
  int execute;
  _XMP_nodes_t *nodes;
  int dim;
  long long lower[_XMP_N_MAX_DIM];
  long long upper[_XMP_N_MAX_DIM];
  unsigned long long stride[_XMP_N_MAX_DIM];
} _XMP_task_desc_t;

// coarray descriptor
#define _XMP_coarray_COMM_t void

typedef struct _XMP_coarray_info_type {
  int size;
  int rank;
} _XMP_coarray_info_t;

typedef struct _XMP_coarray_type {
  void *addr;
  int type;
  size_t type_size;
  unsigned long long total_elmts;

  _XMP_coarray_COMM_t *comm;
  _XMP_coarray_info_t info[1];
} _XMP_coarray_t;

typedef struct _XMP_gpu_array_type {
  int gtol;
  unsigned long long acc;
} _XMP_gpu_array_t;

typedef struct _XMP_gpu_data_type {
  _Bool is_aligned_array;
  void *host_addr;
  void *device_addr;
  _XMP_array_t *host_array_desc;
  _XMP_gpu_array_t *device_array_desc;
  size_t size;
} _XMP_gpu_data_t;

#endif // _XMP_DATA_STRUCT
