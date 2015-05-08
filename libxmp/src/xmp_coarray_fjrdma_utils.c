#include <stdlib.h>
#include <inttypes.h>
#include "xmp_internal.h"

/******************************************************************/
/* DESCRIPTION : Set addresses                                    */
/* ARGUMENT    : [OUT] *addrs     : Addresses                     */
/*               [IN] *base_addr  : Base address                  */
/*               [IN] *array_info : Information of array          */
/*               [IN] dims        : Number of dimensions of array */
/*               [IN] chunk_size  : Chunk size for copy           */
/*               [IN] copy_elmts  : Num of elements for copy      */
/******************************************************************/
void _XMP_set_coarray_addresses_with_chunk(uint64_t* addrs, const uint64_t base_addr, const _XMP_array_section_t* array_info, 
					   const int dims, const size_t chunk_size, const size_t copy_elmts)
{
  uint64_t stride_offset[dims], tmp[dims];

  // Temporally variables to reduce calculation for offset
  for(int i=0;i<dims;i++)
    stride_offset[i] = array_info[i].stride * array_info[i].distance;

  // array_info[dims-1].distance is an element size
  // chunk_size >= array_info[dims-1].distance
  switch (dims){
    int chunk_len;
  case 1:
    chunk_len = chunk_size / array_info[0].distance;
    for(int i=0,num=0;i<array_info[0].length;i+=chunk_len){
      addrs[num++] = stride_offset[0] * i + base_addr;
    }
    break;
  case 2:
    if(array_info[0].distance > chunk_size){ // array_info[0].distance > chunk_size >= array_info[1].distance
      chunk_len = chunk_size / array_info[1].distance;
      for(int i=0,num=0;i<array_info[0].length;i++){
        tmp[0] = stride_offset[0] * i;
        for(int j=0;j<array_info[1].length;j+=chunk_len){
          tmp[1] = stride_offset[1] * j;
          addrs[num++] = tmp[0] + tmp[1] + base_addr;
        }
      }
    }
    else{                               // chunk_size >= array_info[0].distance
      chunk_len = chunk_size / array_info[0].distance;
      for(int i=0,num=0;i<array_info[0].length;i+=chunk_len){
        addrs[num++] = stride_offset[0] * i + base_addr;
      }
    }
    break;
  case 3:
    if(array_info[1].distance > chunk_size){ // array_info[1].distance > chunk_size >= array_info[2].distance
      chunk_len = chunk_size / array_info[2].distance;
      for(int i=0,num=0;i<array_info[0].length;i++){
        tmp[0] = stride_offset[0] * i;
        for(int j=0;j<array_info[1].length;j++){
          tmp[1] = stride_offset[1] * j;
          for(int k=0;k<array_info[2].length;k+=chunk_len){
            tmp[2] = stride_offset[2] * k;
            addrs[num++] = tmp[0] + tmp[1] + tmp[2] + base_addr;
          }
        }
      }
    }
    else if(array_info[0].distance > chunk_size){ // array_info[0].distance > chunk_size >= array_info[1].distance
      chunk_len = chunk_size / array_info[1].distance;
      for(int i=0,num=0;i<array_info[0].length;i++){
        tmp[0] = stride_offset[0] * i;
        for(int j=0;j<array_info[1].length;j+=chunk_len){
          tmp[1] = stride_offset[1] * j;
          addrs[num++] = tmp[0] + tmp[1] + base_addr;
        }
      }
    }
    else{                                   // chunk_size >= array_info[0].distance
      chunk_len = chunk_size / array_info[0].distance;
      for(int i=0,num=0;i<array_info[0].length;i+=chunk_len){
        addrs[num++] = stride_offset[0] * i + base_addr;
      }
    }
    break;
  case 4:
    if(array_info[2].distance > chunk_size){ // array_info[2].distance > chunk_size >= array_info[3].distance
      chunk_len = chunk_size / array_info[3].distance;
      for(int i=0,num=0;i<array_info[0].length;i++){
        tmp[0] = stride_offset[0] * i;
        for(int j=0;j<array_info[1].length;j++){
          tmp[1] = stride_offset[1] * j;
          for(int k=0;k<array_info[2].length;k++){
            tmp[2] = stride_offset[2] * k;
            for(int l=0;l<array_info[3].length;l+=chunk_len){
              tmp[3] = stride_offset[3] * l;
              addrs[num++] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + base_addr;
            }
          }
        }
      }
    }
    else if(array_info[1].distance > chunk_size){ // array_info[1].distance > chunk_size >= array_info[2].distance
      chunk_len = chunk_size / array_info[2].distance;
      for(int i=0,num=0;i<array_info[0].length;i++){
        tmp[0] = stride_offset[0] * i;
        for(int j=0;j<array_info[1].length;j++){
          tmp[1] = stride_offset[1] * j;
          for(int k=0;k<array_info[2].length;k+=chunk_len){
            tmp[2] = stride_offset[2] * k;
            addrs[num++] = tmp[0] + tmp[1] + tmp[2] + base_addr;
          }
        }
      }
    }
    else if(array_info[0].distance > chunk_size){ // array_info[0].distance > chunk_size >= array_info[1].distance
      chunk_len = chunk_size / array_info[1].distance;
      for(int i=0,num=0;i<array_info[0].length;i++){
        tmp[0] = stride_offset[0] * i;
        for(int j=0;j<array_info[1].length;j+=chunk_len){
          tmp[1] = stride_offset[1] * j;
          addrs[num++] = tmp[0] + tmp[1] + base_addr;
        }
      }
    }
    else{                                   // chunk_size >= array_info[0].distance
      chunk_len = chunk_size / array_info[0].distance;
      for(int i=0,num=0;i<array_info[0].length;i+=chunk_len){
        addrs[num++] = stride_offset[0] * i + base_addr;
      }
    }
    break;
  case 5:
    if(array_info[3].distance > chunk_size){ // array_info[3].distance > chunk_size >= array_info[4].distance
      chunk_len = chunk_size / array_info[4].distance;
      for(int i=0,num=0;i<array_info[0].length;i++){
        tmp[0] = stride_offset[0] * i;
        for(int j=0;j<array_info[1].length;j++){
          tmp[1] = stride_offset[1] * j;
          for(int k=0;k<array_info[2].length;k++){
            tmp[2] = stride_offset[2] * k;
            for(int l=0;l<array_info[3].length;l++){
              tmp[3] = stride_offset[3] * l;
              for(int m=0;m<array_info[4].length;m+=chunk_len){
                tmp[4] = stride_offset[4] * m;
                addrs[num++] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4] + base_addr;
              }
            }
          }
        }
      }
    }
    else if(array_info[2].distance > chunk_size){ // array_info[2].distance > chunk_size >= array_info[3].distance
      chunk_len = chunk_size / array_info[3].distance;
      for(int i=0,num=0;i<array_info[0].length;i++){
        tmp[0] = stride_offset[0] * i;
        for(int j=0;j<array_info[1].length;j++){
          tmp[1] = stride_offset[1] * j;
          for(int k=0;k<array_info[2].length;k++){
            tmp[2] = stride_offset[2] * k;
            for(int l=0;l<array_info[3].length;l+=chunk_len){
              tmp[3] = stride_offset[3] * l;
              addrs[num++] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + base_addr;
            }
          }
        }
      }
    }
    else if(array_info[1].distance > chunk_size){ // array_info[1].distance > chunk_size >= array_info[2].distance
      chunk_len = chunk_size / array_info[2].distance;
      for(int i=0,num=0;i<array_info[0].length;i++){
        tmp[0] = stride_offset[0] * i;
        for(int j=0;j<array_info[1].length;j++){
          tmp[1] = stride_offset[1] * j;
          for(int k=0;k<array_info[2].length;k+=chunk_len){
            tmp[2] = stride_offset[2] * k;
            addrs[num++] = tmp[0] + tmp[1] + tmp[2] + base_addr;
          }
        }
      }
    }
    else if(array_info[0].distance > chunk_size){ // array_info[0].distance > chunk_size >= array_info[1].distance
      chunk_len = chunk_size / array_info[1].distance;
      for(int i=0,num=0;i<array_info[0].length;i++){
        tmp[0] = stride_offset[0] * i;
        for(int j=0;j<array_info[1].length;j+=chunk_len){
          tmp[1] = stride_offset[1] * j;
          addrs[num++] = tmp[0] + tmp[1] + base_addr;
        }
      }
    }
    else{                                   // chunk_size >= array_info[0].distance
      chunk_len = chunk_size / array_info[0].distance;
      for(int i=0,num=0;i<array_info[0].length;i+=chunk_len){
        addrs[num++] = stride_offset[0] * i + base_addr;
      }
    }
    break;
  case 6:
    if(array_info[4].distance > chunk_size){ // array_info[4].distance > chunk_size >= array_info[5].distance
      chunk_len = chunk_size / array_info[5].distance;
      for(int i=0,num=0;i<array_info[0].length;i++){
        tmp[0] = stride_offset[0] * i;
        for(int j=0;j<array_info[1].length;j++){
          tmp[1] = stride_offset[1] * j;
          for(int k=0;k<array_info[2].length;k++){
            tmp[2] = stride_offset[2] * k;
            for(int l=0;l<array_info[3].length;l++){
              tmp[3] = stride_offset[3] * l;
              for(int m=0;m<array_info[4].length;m++){
                tmp[4] = stride_offset[4] * m;
                for(int n=0;n<array_info[5].length;n+=chunk_len){
                  tmp[5] = stride_offset[5] * n;
                  addrs[num++] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4] + tmp[5] + base_addr;
                }
              }
            }
          }
        }
      }
    }
    else if(array_info[3].distance > chunk_size){ // array_info[3].distance > chunk_size >= array_info[4].distance
      chunk_len = chunk_size / array_info[4].distance;
      for(int i=0,num=0;i<array_info[0].length;i++){
        tmp[0] = stride_offset[0] * i;
        for(int j=0;j<array_info[1].length;j++){
          tmp[1] = stride_offset[1] * j;
          for(int k=0;k<array_info[2].length;k++){
            tmp[2] = stride_offset[2] * k;
            for(int l=0;l<array_info[3].length;l++){
              tmp[3] = stride_offset[3] * l;
              for(int m=0;m<array_info[4].length;m+=chunk_len){
                tmp[4] = stride_offset[4] * m;
                addrs[num++] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4] + base_addr;
              }
            }
          }
        }
      }
    }
    else if(array_info[2].distance > chunk_size){ // array_info[2].distance > chunk_size >= array_info[3].distance
      chunk_len = chunk_size / array_info[3].distance;
      for(int i=0,num=0;i<array_info[0].length;i++){
        tmp[0] = stride_offset[0] * i;
        for(int j=0;j<array_info[1].length;j++){
          tmp[1] = stride_offset[1] * j;
          for(int k=0;k<array_info[2].length;k++){
            tmp[2] = stride_offset[2] * k;
            for(int l=0;l<array_info[3].length;l+=chunk_len){
              tmp[3] = stride_offset[3] * l;
              addrs[num++] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + base_addr;
            }
          }
        }
      }
    }
    else if(array_info[1].distance > chunk_size){ // array_info[1].distance > chunk_size >= array_info[2].distance
      chunk_len = chunk_size / array_info[2].distance;
      for(int i=0,num=0;i<array_info[0].length;i++){
        tmp[0] = stride_offset[0] * i;
        for(int j=0;j<array_info[1].length;j++){
          tmp[1] = stride_offset[1] * j;
          for(int k=0;k<array_info[2].length;k+=chunk_len){
            tmp[2] = stride_offset[2] * k;
            addrs[num++] = tmp[0] + tmp[1] + tmp[2] + base_addr;
          }
        }
      }
    }
    else if(array_info[0].distance > chunk_size){ // array_info[0].distance > chunk_size >= array_info[1].distance
      chunk_len = chunk_size / array_info[1].distance;
      for(int i=0,num=0;i<array_info[0].length;i++){
        tmp[0] = stride_offset[0] * i;
        for(int j=0;j<array_info[1].length;j+=chunk_len){
          tmp[1] = stride_offset[1] * j;
          addrs[num++] = tmp[0] + tmp[1] + base_addr;
        }
      }
    }
    else{                                   // chunk_size >= array_info[0].distance
      chunk_len = chunk_size / array_info[0].distance;
      for(int i=0,num=0;i<array_info[0].length;i+=chunk_len){
        addrs[num++] = stride_offset[0] * i + base_addr;
      }
    }
    break;
  case 7:
    if(array_info[5].distance > chunk_size){ // array_info[5].distance > chunk_size >= array_info[6].distance
      chunk_len = chunk_size / array_info[6].distance;
      for(int i=0,num=0;i<array_info[0].length;i++){
        tmp[0] = stride_offset[0] * i;
        for(int j=0;j<array_info[1].length;j++){
          tmp[1] = stride_offset[1] * j;
          for(int k=0;k<array_info[2].length;k++){
            tmp[2] = stride_offset[2] * k;
            for(int l=0;l<array_info[3].length;l++){
              tmp[3] = stride_offset[3] * l;
              for(int m=0;m<array_info[4].length;m++){
                tmp[4] = stride_offset[4] * m;
                for(int n=0;n<array_info[5].length;n++){
                  tmp[5] = stride_offset[5] * n;
                  for(int p=0;p<array_info[6].length;p+=chunk_len){
                    tmp[6] = stride_offset[6] * p;
                    addrs[num++] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4] + tmp[5] + tmp[6] + base_addr;
                  }
                }
              }
            }
          }
        }
      }
    }
    else if(array_info[4].distance > chunk_size){ // array_info[4].distance > chunk_size >= array_info[5].distance
      chunk_len = chunk_size / array_info[5].distance;
      for(int i=0,num=0;i<array_info[0].length;i++){
        tmp[0] = stride_offset[0] * i;
        for(int j=0;j<array_info[1].length;j++){
          tmp[1] = stride_offset[1] * j;
          for(int k=0;k<array_info[2].length;k++){
            tmp[2] = stride_offset[2] * k;
            for(int l=0;l<array_info[3].length;l++){
              tmp[3] = stride_offset[3] * l;
              for(int m=0;m<array_info[4].length;m++){
                tmp[4] = stride_offset[4] * m;
                for(int n=0;n<array_info[5].length;n+=chunk_len){
                  tmp[5] = stride_offset[5] * n;
                  addrs[num++] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4] + tmp[5] + base_addr;
                }
              }
            }
          }
        }
      }
    }
    else if(array_info[3].distance > chunk_size){ // array_info[3].distance > chunk_size >= array_info[4].distance
      chunk_len = chunk_size / array_info[4].distance;
      for(int i=0,num=0;i<array_info[0].length;i++){
        tmp[0] = stride_offset[0] * i;
        for(int j=0;j<array_info[1].length;j++){
          tmp[1] = stride_offset[1] * j;
          for(int k=0;k<array_info[2].length;k++){
            tmp[2] = stride_offset[2] * k;
            for(int l=0;l<array_info[3].length;l++){
              tmp[3] = stride_offset[3] * l;
              for(int m=0;m<array_info[4].length;m+=chunk_len){
                tmp[4] = stride_offset[4] * m;
                addrs[num++] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4] + base_addr;
              }
            }
          }
        }
      }
    }
    else if(array_info[2].distance > chunk_size){ // array_info[2].distance > chunk_size >= array_info[3].distance
      chunk_len = chunk_size / array_info[3].distance;
      for(int i=0,num=0;i<array_info[0].length;i++){
        tmp[0] = stride_offset[0] * i;
        for(int j=0;j<array_info[1].length;j++){
          tmp[1] = stride_offset[1] * j;
          for(int k=0;k<array_info[2].length;k++){
            tmp[2] = stride_offset[2] * k;
            for(int l=0;l<array_info[3].length;l+=chunk_len){
              tmp[3] = stride_offset[3] * l;
              addrs[num++] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + base_addr;
            }
          }
        }
      }
    }
    else if(array_info[1].distance > chunk_size){ // array_info[1].distance > chunk_size >= array_info[2].distance
      chunk_len = chunk_size / array_info[2].distance;
      for(int i=0,num=0;i<array_info[0].length;i++){
	tmp[0] = stride_offset[0] * i;
	for(int j=0;j<array_info[1].length;j++){
	  tmp[1] = stride_offset[1] * j;
	  for(int k=0;k<array_info[2].length;k+=chunk_len){
	    tmp[2] = stride_offset[2] * k;
	    addrs[num++] = tmp[0] + tmp[1] + tmp[2] + base_addr;
	  }
	}
      }
    }
    else if(array_info[0].distance > chunk_size){ // array_info[0].distance > chunk_size >= array_info[1].distance
      chunk_len = chunk_size / array_info[1].distance;
      for(int i=0,num=0;i<array_info[0].length;i++){
        tmp[0] = stride_offset[0] * i;
        for(int j=0;j<array_info[1].length;j+=chunk_len){
          tmp[1] = stride_offset[1] * j;
          addrs[num++] = tmp[0] + tmp[1] + base_addr;
        }
      }
    }
    else{                                   // chunk_size >= array_info[0].distance
      chunk_len = chunk_size / array_info[0].distance;
      for(int i=0,num=0;i<array_info[0].length;i+=chunk_len){
        addrs[num++] = stride_offset[0] * i + base_addr;
      }
    }
    break;
  }
}

void _XMP_set_coarray_addresses(const uint64_t addr, const _XMP_array_section_t *array, const int dims, 
				const size_t elmts, uint64_t* addrs)
{
  uint64_t stride_offset[dims], tmp[dims];

  // Temporally variables to reduce calculation for offset
  for(int i=0;i<dims;i++)
    stride_offset[i] = array[i].stride * array[i].distance;
 
  switch (dims){
  case 1:
    for(int i=0, num=0;i<array[0].length;i++){
      tmp[0] = stride_offset[0] * i;
      addrs[num++] = addr + tmp[0];
    }
    break;
  case 2:
    for(int i=0, num=0;i<array[0].length;i++){
      tmp[0] = stride_offset[0] * i;
      for(int j=0;j<array[1].length;j++){
        tmp[1] = stride_offset[1] * j;
	addrs[num++] = addr + tmp[0] + tmp[1];
      }
    }
    break;
  case 3:
    for(int i=0, num=0;i<array[0].length;i++){
      tmp[0] = stride_offset[0] * i;
      for(int j=0;j<array[1].length;j++){
        tmp[1] = stride_offset[1] * j;
	for(int k=0;k<array[2].length;k++){
	  tmp[2] = stride_offset[2] * k;
	  addrs[num++] = addr + tmp[0] + tmp[1] + tmp[2];
	}
      }
    }
    break;
  case 4:
    for(int i=0, num=0;i<array[0].length;i++){
      tmp[0] = stride_offset[0] * i;
      for(int j=0;j<array[1].length;j++){
        tmp[1] = stride_offset[1] * j;
	for(int k=0;k<array[2].length;k++){
          tmp[2] = stride_offset[2] * k;
	  for(int l=0;l<array[3].length;l++){
	    tmp[3] = stride_offset[3] * l;
	    addrs[num++] = addr + tmp[0] + tmp[1] + tmp[2] + tmp[3];
	  }
	}
      }
    }
    break;
  case 5:
    for(int i=0, num=0;i<array[0].length;i++){
      tmp[0] = stride_offset[0] * i;
      for(int j=0;j<array[1].length;j++){
        tmp[1] = stride_offset[1] * j;
        for(int k=0;k<array[2].length;k++){
          tmp[2] = stride_offset[2] * k;
          for(int l=0;l<array[3].length;l++){
            tmp[3] = stride_offset[3] * l;
	    for(int m=0;m<array[4].length;m++){
	      tmp[4] = stride_offset[4] * m;
	      addrs[num++] = addr + tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4];
	    }
          }
        }
      }
    }
    break;
  case 6:
    for(int i=0, num=0;i<array[0].length;i++){
      tmp[0] = stride_offset[0] * i;
      for(int j=0;j<array[1].length;j++){
        tmp[1] = stride_offset[1] * j;
        for(int k=0;k<array[2].length;k++){
          tmp[2] = stride_offset[2] * k;
          for(int l=0;l<array[3].length;l++){
            tmp[3] = stride_offset[3] * l;
            for(int m=0;m<array[4].length;m++){
              tmp[4] = stride_offset[4] * m;
	      for(int n=0;n<array[5].length;n++){
		tmp[5] = stride_offset[5] * n;
		addrs[num++] = addr + tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4] + tmp[5];
	      }
            }
          }
        }
      }
    }
    break;
  case 7:
    for(int i=0, num=0;i<array[0].length;i++){
      tmp[0] = stride_offset[0] * i;
      for(int j=0;j<array[1].length;j++){
        tmp[1] = stride_offset[1] * j;
        for(int k=0;k<array[2].length;k++){
          tmp[2] = stride_offset[2] * k;
          for(int l=0;l<array[3].length;l++){
            tmp[3] = stride_offset[3] * l;
            for(int m=0;m<array[4].length;m++){
              tmp[4] = stride_offset[4] * m;
              for(int n=0;n<array[5].length;n++){
                tmp[5] = stride_offset[5] * n;
		for(int p=0;p<array[6].length;p++){
		  tmp[6] = stride_offset[6] * p;
		  addrs[num++] = addr + tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4] + tmp[5] + tmp[6];
		}
	      }
            }
          }
        }
      }
    }
    break;
  }
}

/***************************************************************************/
/* DESCRIPTION : Check the dimension of an array has all element ?         */
/* ARGUMENT    : [IN] *array_info : Information of array                   */
/*               [IN] dim         : Dimension                              */
/* RETURN:     : If the dimension of an array has all element, return TRUE */
/***************************************************************************/
static int _is_all_element(const _XMP_array_section_t *array_info, int dim){
  if(array_info[dim].elmts == array_info[dim].length)
    return _XMP_N_INT_TRUE;
  else
    return _XMP_N_INT_FALSE;
}

/**
   If 1dim array has a constant stride, return TRUE (Always TRUE)
*/
int _XMP_is_constant_stride_1dim()
{
  return _XMP_N_INT_TRUE;
}

/********************************************************************/
/* DESCRIPTION : Is 2dim array has a constant stride ?              */
/* ARGUMENT    : [IN] *array_info : Information of array            */
/*               [IN] array_dims  : Number of dimensions of array   */
/* RETURN:     : If 2dim array has a constant stride, return TRUE   */
/********************************************************************/
int _XMP_is_constant_stride_2dim(const _XMP_array_section_t *array_info,
				 const int array_dims)
{
  if(array_info[array_dims-1].stride == 1){
    return _XMP_N_INT_TRUE;
  }
  else if(array_info[array_dims-2].length == 1){
    return _XMP_is_constant_stride_1dim();
  }

  return _XMP_N_INT_FALSE;
}

/********************************************************************/
/* DESCRIPTION : Is 3dim array has a constant stride ?              */
/* ARGUMENT    : [IN] *array_info : Information of array            */
/*               [IN] array_dims  : Number of dimensions of array   */
/* RETURN:     : If 3dim array has a constant stride, return TRUE   */
/********************************************************************/
int _XMP_is_constant_stride_3dim(const _XMP_array_section_t *array_info,
				 const int array_dims)
{
  if(array_info[array_dims-2].stride == 1 && _is_all_element(array_info, array_dims-1)){
    return _XMP_N_INT_TRUE;
  }
  else if(array_info[array_dims-3].length == 1 && array_info[array_dims-2].length == 1){
    return _XMP_is_constant_stride_1dim();
  }
  else if(array_info[array_dims-3].length == 1){
    return _XMP_is_constant_stride_2dim(array_info, array_dims);
  }

  return _XMP_N_INT_FALSE;
}

/********************************************************************/
/* DESCRIPTION : Is 4dim array has a constant stride ?              */
/* ARGUMENT    : [IN] *array_info : Information of array            */
/*               [IN] array_dims  : Number of dimensions of array   */
/* RETURN:     : If 4dim array has a constant stride, return TRUE   */
/********************************************************************/
int _XMP_is_constant_stride_4dim(const _XMP_array_section_t *array_info,
				 const int array_dims)
{
  if(array_info[array_dims-3].stride == 1 && _is_all_element(array_info, array_dims-2) &&
     _is_all_element(array_info, array_dims-1)){
    return _XMP_N_INT_TRUE;
  }
  else if(array_info[array_dims-4].length == 1 && array_info[array_dims-3].length == 1 &&
          array_info[array_dims-2].length == 1){
    return _XMP_is_constant_stride_1dim();
  }
  else if(array_info[array_dims-4].length == 1 && array_info[array_dims-3].length == 1){
    return _XMP_is_constant_stride_2dim(array_info, array_dims);
  }
  else if(array_info[array_dims-4].length == 1){
    return _XMP_is_constant_stride_3dim(array_info, array_dims);
  }

  return _XMP_N_INT_FALSE;
}

/********************************************************************/
/* DESCRIPTION : Is 5dim array has a constant stride ?              */
/* ARGUMENT    : [IN] *array_info : Information of array            */
/*               [IN] array_dims  : Number of dimensions of array   */
/* RETURN:     : If 5dim array has a constant stride, return TRUE   */
/********************************************************************/
int _XMP_is_constant_stride_5dim(const _XMP_array_section_t *array_info,
				 const int array_dims)
{
  if(array_info[array_dims-4].stride == 1 && _is_all_element(array_info, array_dims-3) &&
     _is_all_element(array_info, array_dims-2) && _is_all_element(array_info, array_dims-1)){
    return _XMP_N_INT_TRUE;
  }
  else if(array_info[array_dims-5].length == 1 && array_info[array_dims-4].length == 1 &&
          array_info[array_dims-3].length == 1 && array_info[array_dims-2].length == 1){
    return _XMP_is_constant_stride_1dim();
  }
  else if(array_info[array_dims-5].length == 1 && array_info[array_dims-4].length == 1 &&
          array_info[array_dims-3].length == 1){
    return _XMP_is_constant_stride_2dim(array_info, array_dims);
  }
  else if(array_info[array_dims-5].length == 1 && array_info[array_dims-4].length == 1){
    return _XMP_is_constant_stride_3dim(array_info, array_dims);
  }
  else if(array_info[array_dims-5].length == 1){
    return _XMP_is_constant_stride_4dim(array_info, array_dims);
  }

  return _XMP_N_INT_FALSE;
}

/********************************************************************/
/* DESCRIPTION : Is 6dim array has a constant stride ?              */
/* ARGUMENT    : [IN] *array_info : Information of array            */
/*               [IN] array_dims  : Number of dimensions of array   */
/* RETURN:     : If 6dim array has a constant stride, return TRUE   */
/********************************************************************/
int _XMP_is_constant_stride_6dim(const _XMP_array_section_t *array_info,
				 const int array_dims)
{
  if(array_info[array_dims-5].stride == 1 && _is_all_element(array_info, array_dims-4) &&
     _is_all_element(array_info, array_dims-3) && _is_all_element(array_info, array_dims-2) &&
     _is_all_element(array_info, array_dims-1)){
    return _XMP_N_INT_TRUE;
  }
  else if(array_info[array_dims-6].length == 1 && array_info[array_dims-5].length == 1 &&
          array_info[array_dims-4].length == 1 && array_info[array_dims-3].length == 1 &&
          array_info[array_dims-2].length == 1){
    return _XMP_is_constant_stride_1dim();
  }
  else if(array_info[array_dims-6].length == 1 && array_info[array_dims-5].length == 1 &&
          array_info[array_dims-4].length == 1 && array_info[array_dims-3].length == 1){
    return _XMP_is_constant_stride_2dim(array_info, array_dims);
  }
  else if(array_info[array_dims-6].length == 1 && array_info[array_dims-5].length == 1 &&
          array_info[array_dims-4].length == 1){
    return _XMP_is_constant_stride_3dim(array_info, array_dims);
  }
  else if(array_info[array_dims-6].length == 1 && array_info[array_dims-5].length == 1){
    return _XMP_is_constant_stride_4dim(array_info, array_dims);
  }
  else if(array_info[array_dims-6].length == 1){
    return _XMP_is_constant_stride_5dim(array_info, array_dims);
  }

  return _XMP_N_INT_FALSE;
}

/********************************************************************/
/* DESCRIPTION : Is 7dim array has a constant stride ?              */
/* ARGUMENT    : [IN] *array_info : Information of array            */
/*               [IN] array_dims  : Number of dimensions of array   */
/* RETURN:     : If 7dim array has a constant stride, return TRUE   */
/********************************************************************/
int _XMP_is_constant_stride_7dim(const _XMP_array_section_t *array_info,
				 const int array_dims)
{
  if(array_info[array_dims-6].stride == 1 && _is_all_element(array_info, array_dims-5) &&
     _is_all_element(array_info, array_dims-4) && _is_all_element(array_info, array_dims-3) &&
     _is_all_element(array_info, array_dims-2) && _is_all_element(array_info, array_dims-1)){
    return _XMP_N_INT_TRUE;
  }
  else if(array_info[array_dims-7].length == 1 && array_info[array_dims-6].length == 1 &&
          array_info[array_dims-5].length == 1 && array_info[array_dims-4].length == 1 &&
          array_info[array_dims-3].length == 1 && array_info[array_dims-2].length == 1){
    return _XMP_is_constant_stride_1dim();
  }
  else if(array_info[array_dims-7].length == 1 && array_info[array_dims-6].length == 1 &&
          array_info[array_dims-5].length == 1 && array_info[array_dims-4].length == 1 &&
          array_info[array_dims-3].length == 1){
    return _XMP_is_constant_stride_2dim(array_info, array_dims);
  }
  else if(array_info[array_dims-7].length == 1 && array_info[array_dims-6].length == 1 &&
          array_info[array_dims-5].length == 1 && array_info[array_dims-4].length == 1){
    return _XMP_is_constant_stride_3dim(array_info, array_dims);
  }
  else if(array_info[array_dims-7].length == 1 && array_info[array_dims-6].length == 1 &&
          array_info[array_dims-5].length == 1){
    return _XMP_is_constant_stride_4dim(array_info, array_dims);
  }
  else if(array_info[array_dims-7].length == 1 && array_info[array_dims-6].length == 1){
    return _XMP_is_constant_stride_5dim(array_info, array_dims);
  }
  else if(array_info[array_dims-7].length == 1){
    return _XMP_is_constant_stride_6dim(array_info, array_dims);
  }

  return _XMP_N_INT_FALSE;
}

/***************************************************************/
/* DESCRIPTION : Caluculate stride size of array               */
/* ARGUMENT    : [IN] *array_info : Information of array       */
/*               [IN] dims        : Demension of array         */
/*               [IN] chunk_size  : Size of chunk              */
/* RETURN:     : Stride size                                   */
/***************************************************************/
size_t _XMP_calc_stride(const _XMP_array_section_t *array_info, const int dims,
			const size_t chunk_size)
{
  uint64_t stride_offset[dims], tmp[dims];
  size_t stride[2];

  // Temporally variables to reduce calculation for offset
  for(int i=0;i<dims;i++)
    stride_offset[i] = array_info[i].stride * array_info[i].distance;

  switch (dims){
    int chunk_len;
  case 1:
    chunk_len = chunk_size / array_info[0].distance;
    for(int i=0,num=0;i<array_info[0].length;i+=chunk_len){
      stride[num++] = stride_offset[0] * chunk_len * i;
      if(num == 2) goto end;
    }
  case 2:
    if(array_info[0].distance > chunk_size){ // array_info[0].distance > chunk_size >= array_info[1].distance
      chunk_len = chunk_size / array_info[1].distance;
      for(int i=0,num=0;i<array_info[0].length;i++){
        tmp[0] = stride_offset[0] * i;
        for(int j=0;j<array_info[1].length;j+=chunk_len){
          tmp[1] = stride_offset[1] * j;
          stride[num++] = tmp[0] + tmp[1];
          if(num == 2) goto end;
        }
      }
    }
    else{                               // chunk_size >= array_info[0].distance
      chunk_len = chunk_size / array_info[0].distance;
      for(int i=0,num=0;i<array_info[0].length;i+=chunk_len){
        stride[num++] = stride_offset[0] * i;
        if(num == 2) goto end;
      }
    }
  case 3:
   if(array_info[1].distance > chunk_size){ // array_info[1].distance > chunk_size >= array_info[2].distance
     chunk_len = chunk_size / array_info[2].distance;
     for(int i=0,num=0;i<array_info[0].length;i++){
       tmp[0] = stride_offset[0] * i;
       for(int j=0;j<array_info[1].length;j++){
	 tmp[1] = stride_offset[1] * j;
	 for(int k=0;k<array_info[2].length;k+=chunk_len){
	   tmp[2] = stride_offset[2] * k;
	   stride[num++] = tmp[0] + tmp[1] + tmp[2];
	   if(num == 2) goto end;
	 }
       }
     }
   }
   else if(array_info[0].distance > chunk_size){ // array_info[0].distance > chunk_size >= array_info[1].distance
     chunk_len = chunk_size / array_info[1].distance;
     for(int i=0,num=0;i<array_info[0].length;i++){
       tmp[0] = stride_offset[0] * i;
       for(int j=0;j<array_info[1].length;j+=chunk_len){
	 tmp[1] = stride_offset[1] * j;
	 stride[num++] = tmp[0] + tmp[1];
	 if(num == 2) goto end;
       }
     }
   }
   else{                                   // chunk_size >= array_info[0].distance
     chunk_len = chunk_size / array_info[0].distance;
     for(int i=0,num=0;i<array_info[0].length;i+=chunk_len){
       stride[num++] = stride_offset[0] * i;
       if(num == 2) goto end;
     }
   }
   break;
 case 4:
   if(array_info[2].distance > chunk_size){ // array_info[2].distance > chunk_size >= array_info[3].distance
     chunk_len = chunk_size / array_info[3].distance;
     for(int i=0,num=0;i<array_info[0].length;i++){
       tmp[0] = stride_offset[0] * i;
       for(int j=0;j<array_info[1].length;j++){
	 tmp[1] = stride_offset[1] * j;
	 for(int k=0;k<array_info[2].length;k++){
	   tmp[2] = stride_offset[2] * k;
	   for(int l=0;l<array_info[3].length;l+=chunk_len){
	     tmp[3] = stride_offset[3] * l;
	     stride[num++] = tmp[0] + tmp[1] + tmp[2] + tmp[3];
	     if(num == 2) goto end;
	   }
	 }
       }
     }
   }
   else if(array_info[1].distance > chunk_size){ // array_info[1].distance > chunk_size >= array_info[2].distance
     chunk_len = chunk_size / array_info[2].distance;
     for(int i=0,num=0;i<array_info[0].length;i++){
       tmp[0] = stride_offset[0] * i;
       for(int j=0;j<array_info[1].length;j++){
	 tmp[1] = stride_offset[1] * j;
	 for(int k=0;k<array_info[2].length;k+=chunk_len){
	   tmp[2] = stride_offset[2] * k;
	   stride[num++] = tmp[0] + tmp[1] + tmp[2];
	   if(num == 2) goto end;
	 }
       }
     }
   }
   else if(array_info[0].distance > chunk_size){ // array_info[0].distance > chunk_size >= array_info[1].distance
     chunk_len = chunk_size / array_info[1].distance;
     for(int i=0,num=0;i<array_info[0].length;i++){
       tmp[0] = stride_offset[0] * i;
       for(int j=0;j<array_info[1].length;j+=chunk_len){
	 tmp[1] = stride_offset[1] * j;
	 stride[num++] = tmp[0] + tmp[1];
	 if(num == 2) goto end;
       }
     }
   }
   else{                                   // chunk_size >= array_info[0].distance
     chunk_len = chunk_size / array_info[0].distance;
     for(int i=0,num=0;i<array_info[0].length;i+=chunk_len){
       stride[num++] = stride_offset[0] * i;
       if(num == 2) goto end;
     }
   }
   break;
 case 5:
   if(array_info[3].distance > chunk_size){ // array_info[3].distance > chunk_size >= array_info[4].distance
     chunk_len = chunk_size / array_info[4].distance;
     for(int i=0,num=0;i<array_info[0].length;i++){
       tmp[0] = stride_offset[0] * i;
       for(int j=0;j<array_info[1].length;j++){
	 tmp[1] = stride_offset[1] * j;
	 for(int k=0;k<array_info[2].length;k++){
	   tmp[2] = stride_offset[2] * k;
	   for(int l=0;l<array_info[3].length;l++){
	     tmp[3] = stride_offset[3] * l;
	     for(int m=0;m<array_info[4].length;m+=chunk_len){
	       tmp[4] = stride_offset[4] * m;
	       stride[num++] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4];
	       if(num == 2) goto end;
	     }
	   }
	 }
       }
     }
   }
   else if(array_info[2].distance > chunk_size){ // array_info[2].distance > chunk_size >= array_info[3].distance
     chunk_len = chunk_size / array_info[3].distance;
     for(int i=0,num=0;i<array_info[0].length;i++){
       tmp[0] = stride_offset[0] * i;
       for(int j=0;j<array_info[1].length;j++){
	 tmp[1] = stride_offset[1] * j;
	 for(int k=0;k<array_info[2].length;k++){
	   tmp[2] = stride_offset[2] * k;
	   for(int l=0;l<array_info[3].length;l+=chunk_len){
	     tmp[3] = stride_offset[3] * l;
	     stride[num++] = tmp[0] + tmp[1] + tmp[2] + tmp[3];
	     if(num == 2) goto end;
	   }
	 }
       }
     }
   }
   else if(array_info[1].distance > chunk_size){ // array_info[1].distance > chunk_size >= array_info[2].distance
     chunk_len = chunk_size / array_info[2].distance;
     for(int i=0,num=0;i<array_info[0].length;i++){
       tmp[0] = stride_offset[0] * i;
       for(int j=0;j<array_info[1].length;j++){
	 tmp[1] = stride_offset[1] * j;
	 for(int k=0;k<array_info[2].length;k+=chunk_len){
	   tmp[2] = stride_offset[2] * k;
	   stride[num++] = tmp[0] + tmp[1] + tmp[2];
	   if(num == 2) goto end;
	 }
       }
     }
   }
   else if(array_info[0].distance > chunk_size){ // array_info[0].distance > chunk_size >= array_info[1].distance
     chunk_len = chunk_size / array_info[1].distance;
     for(int i=0,num=0;i<array_info[0].length;i++){
       tmp[0] = stride_offset[0] * i;
       for(int j=0;j<array_info[1].length;j+=chunk_len){
	 tmp[1] = stride_offset[1] * j;
	 stride[num++] = tmp[0] + tmp[1];
	 if(num == 2) goto end;
       }
     }
   }
   else{                                   // chunk_size >= array_info[0].distance
     chunk_len = chunk_size / array_info[0].distance;
     for(int i=0,num=0;i<array_info[0].length;i+=chunk_len){
       stride[num++] = stride_offset[0] * i;
       if(num == 2) goto end;
     }
   }
   break;
 case 6:
   if(array_info[4].distance > chunk_size){ // array_info[4].distance > chunk_size >= array_info[5].distance
     chunk_len = chunk_size / array_info[5].distance;
     for(int i=0,num=0;i<array_info[0].length;i++){
       tmp[0] = stride_offset[0] * i;
       for(int j=0;j<array_info[1].length;j++){
	 tmp[1] = stride_offset[1] * j;
	 for(int k=0;k<array_info[2].length;k++){
	   tmp[2] = stride_offset[2] * k;
	   for(int l=0;l<array_info[3].length;l++){
	     tmp[3] = stride_offset[3] * l;
	     for(int m=0;m<array_info[4].length;m++){
	       tmp[4] = stride_offset[4] * m;
	       for(int n=0;n<array_info[5].length;n+=chunk_len){
		 tmp[5] = stride_offset[5] * n;
		 stride[num++] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4] + tmp[5];
		 if(num == 2) goto end;
	       }
	     }
	   }
	 }
       }
     }
   }
   else if(array_info[3].distance > chunk_size){ // array_info[3].distance > chunk_size >= array_info[4].distance
     chunk_len = chunk_size / array_info[4].distance;
     for(int i=0,num=0;i<array_info[0].length;i++){
       tmp[0] = stride_offset[0] * i;
       for(int j=0;j<array_info[1].length;j++){
	 tmp[1] = stride_offset[1] * j;
	 for(int k=0;k<array_info[2].length;k++){
	   tmp[2] = stride_offset[2] * k;
	   for(int l=0;l<array_info[3].length;l++){
	     tmp[3] = stride_offset[3] * l;
	     for(int m=0;m<array_info[4].length;m+=chunk_len){
	       tmp[4] = stride_offset[4] * m;
	       stride[num++] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4];
               if(num == 2) goto end;
	     }
	   }
	 }
       }
     }
   }
   else if(array_info[2].distance > chunk_size){ // array_info[2].distance > chunk_size >= array_info[3].distance
     chunk_len = chunk_size / array_info[3].distance;
     for(int i=0,num=0;i<array_info[0].length;i++){
       tmp[0] = stride_offset[0] * i;
       for(int j=0;j<array_info[1].length;j++){
	 tmp[1] = stride_offset[1] * j;
	 for(int k=0;k<array_info[2].length;k++){
	   tmp[2] = stride_offset[2] * k;
	   for(int l=0;l<array_info[3].length;l+=chunk_len){
	     tmp[3] = stride_offset[3] * l;
	     stride[num++] = tmp[0] + tmp[1] + tmp[2] + tmp[3];
	     if(num == 2) goto end;
	   }
	 }
       }
     }
   }
   else if(array_info[1].distance > chunk_size){ // array_info[1].distance > chunk_size >= array_info[2].distance
     chunk_len = chunk_size / array_info[2].distance;
     for(int i=0,num=0;i<array_info[0].length;i++){
       tmp[0] = stride_offset[0] * i;
       for(int j=0;j<array_info[1].length;j++){
	 tmp[1] = stride_offset[1] * j;
	 for(int k=0;k<array_info[2].length;k+=chunk_len){
	   tmp[2] = stride_offset[2] * k;
	   stride[num++] = tmp[0] + tmp[1] + tmp[2];
	   if(num == 2) goto end;
	 }
       }
     }
   }
   else if(array_info[0].distance > chunk_size){ // array_info[0].distance > chunk_size >= array_info[1].distance
     chunk_len = chunk_size / array_info[1].distance;
     for(int i=0,num=0;i<array_info[0].length;i++){
       tmp[0] = stride_offset[0] * i;
       for(int j=0;j<array_info[1].length;j+=chunk_len){
	 tmp[1] = stride_offset[1] * j;
	 stride[num++] = tmp[0] + tmp[1];
	 if(num == 2) goto end;
       }
     }
   }
   else{                                   // chunk_size >= array_info[0].distance
     chunk_len = chunk_size / array_info[0].distance;
     for(int i=0,num=0;i<array_info[0].length;i+=chunk_len){
       stride[num++] = stride_offset[0] * i;
       if(num == 2) goto end;
     }
   }
   break;
 case 7:
   if(array_info[5].distance > chunk_size){ // array_info[5].distance > chunk_size >= array_info[6].distance
     chunk_len = chunk_size / array_info[6].distance;
     for(int i=0,num=0;i<array_info[0].length;i++){
       tmp[0] = stride_offset[0] * i;
       for(int j=0;j<array_info[1].length;j++){
	 tmp[1] = stride_offset[1] * j;
	 for(int k=0;k<array_info[2].length;k++){
	   tmp[2] = stride_offset[2] * k;
	   for(int l=0;l<array_info[3].length;l++){
	     tmp[3] = stride_offset[3] * l;
	     for(int m=0;m<array_info[4].length;m++){
	       tmp[4] = stride_offset[4] * m;
	       for(int n=0;n<array_info[5].length;n++){
		 tmp[5] = stride_offset[5] * n;
		 for(int p=0;p<array_info[6].length;p+=chunk_len){
		   tmp[6] = stride_offset[6] * p;
		   stride[num++] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4] + tmp[5] + tmp[6];
		   if(num == 2) goto end;
		 }
	       }
	     }
	   }
	 }
       }
     }
   }
   else if(array_info[4].distance > chunk_size){ // array_info[4].distance > chunk_size >= array_info[5].distance
     chunk_len = chunk_size / array_info[5].distance;
     for(int i=0,num=0;i<array_info[0].length;i++){
       tmp[0] = stride_offset[0] * i;
       for(int j=0;j<array_info[1].length;j++){
	 tmp[1] = stride_offset[1] * j;
	 for(int k=0;k<array_info[2].length;k++){
	   tmp[2] = stride_offset[2] * k;
	   for(int l=0;l<array_info[3].length;l++){
	     tmp[3] = stride_offset[3] * l;
	     for(int m=0;m<array_info[4].length;m++){
	       tmp[4] = stride_offset[4] * m;
	       for(int n=0;n<array_info[5].length;n+=chunk_len){
		 tmp[5] = stride_offset[5] * n;
		 stride[num++] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4] + tmp[5];
		 if(num == 2) goto end;
	       }
	     }
	   }
	 }
       }
     }
   }
   else if(array_info[3].distance > chunk_size){ // array_info[3].distance > chunk_size >= array_info[4].distance
     chunk_len = chunk_size / array_info[4].distance;
     for(int i=0,num=0;i<array_info[0].length;i++){
       tmp[0] = stride_offset[0] * i;
       for(int j=0;j<array_info[1].length;j++){
	 tmp[1] = stride_offset[1] * j;
	 for(int k=0;k<array_info[2].length;k++){
	   tmp[2] = stride_offset[2] * k;
	   for(int l=0;l<array_info[3].length;l++){
	     tmp[3] = stride_offset[3] * l;
	     for(int m=0;m<array_info[4].length;m+=chunk_len){
	       tmp[4] = stride_offset[4] * m;
	       stride[num++] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4];
               if(num == 2) goto end;
	     }
	   }
	 }
       }
     }
   }
   else if(array_info[2].distance > chunk_size){ // array_info[2].distance > chunk_size >= array_info[3].distance
     chunk_len = chunk_size / array_info[3].distance;
     for(int i=0,num=0;i<array_info[0].length;i++){
       tmp[0] = stride_offset[0] * i;
       for(int j=0;j<array_info[1].length;j++){
	 tmp[1] = stride_offset[1] * j;
	 for(int k=0;k<array_info[2].length;k++){
	   tmp[2] = stride_offset[2] * k;
	   for(int l=0;l<array_info[3].length;l+=chunk_len){
	     tmp[3] = stride_offset[3] * l;
	     stride[num++] = tmp[0] + tmp[1] + tmp[2] + tmp[3];
	     if(num == 2) goto end;
	   }
	 }
       }
     }
   }
   else if(array_info[1].distance > chunk_size){ // array_info[1].distance > chunk_size >= array_info[2].distance
     chunk_len = chunk_size / array_info[2].distance;
     for(int i=0,num=0;i<array_info[0].length;i++){
       tmp[0] = stride_offset[0] * i;
       for(int j=0;j<array_info[1].length;j++){
	 tmp[1] = stride_offset[1] * j;
	 for(int k=0;k<array_info[2].length;k+=chunk_len){
	   tmp[2] = stride_offset[2] * k;
	   stride[num++] = tmp[0] + tmp[1] + tmp[2];
	   if(num == 2) goto end;
	 }
       }
     }
   }
   else if(array_info[0].distance > chunk_size){ // array_info[0].distance > chunk_size >= array_info[1].distance
     chunk_len = chunk_size / array_info[1].distance;
     for(int i=0,num=0;i<array_info[0].length;i++){
       tmp[0] = stride_offset[0] * i;
       for(int j=0;j<array_info[1].length;j+=chunk_len){
	 tmp[1] = stride_offset[1] * j;
	 stride[num++] = tmp[0] + tmp[1];
	 if(num == 2) goto end;
       }
     }
   }
   else{                                   // chunk_size >= array_info[0].distance
     chunk_len = chunk_size / array_info[0].distance;
     for(int i=0,num=0;i<array_info[0].length;i+=chunk_len){
       stride[num++] = stride_offset[0] * i;
       if(num == 2) goto end;
     }
   }
   break;
  }

 end:
  return stride[1] - stride[0];
}
