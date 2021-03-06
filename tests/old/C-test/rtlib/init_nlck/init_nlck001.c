static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* omp_init_nest_lock 001:
 * omp_init_nest_lock の動作確認
 */

#include <omp.h>
#include "omni.h"


main ()
{
  omp_nest_lock_t	lck;
  int			t;

  int	errors = 0;


  omp_init_nest_lock (&lck);	      /* 1st initialize */
  omp_set_nest_lock (&lck);
  omp_unset_nest_lock (&lck);
  omp_destroy_nest_lock (&lck);

  omp_init_nest_lock (&lck);	      /* 2nd initialize */
  omp_set_nest_lock (&lck);
  omp_unset_nest_lock (&lck);
  omp_destroy_nest_lock (&lck);

  omp_init_nest_lock (&lck);	      /* 3rd initialize */
  t = omp_test_nest_lock (&lck);
  if (t == 0) {
    errors += 1;
  }
  omp_unset_nest_lock (&lck);
  omp_destroy_nest_lock (&lck);

  omp_init_nest_lock (&lck);	      /* 4th initialize */
  t = omp_test_nest_lock (&lck);
  if (t != 1) {
    errors += 1;
  }
  t = omp_test_nest_lock (&lck);
  if (t != 2) {
    errors += 1;
  }
  omp_unset_nest_lock (&lck);
  omp_unset_nest_lock (&lck);
  omp_destroy_nest_lock (&lck);

  if (errors == 0) {
    printf ("omp_init_nest_lock 001 : SUCCESS\n");
    return 0;
  } else {
    printf ("omp_init_nest_lock 001 : FAILED\n");
    return 1;
  }
}
