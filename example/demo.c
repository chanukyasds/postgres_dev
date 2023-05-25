#include <stdio.h>
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>

int
main ()
{

  double alpha = 0;
  double df1 = 0;
  double df2 = 2;
  
  gsl_set_error_handler_off();

  double val = gsl_cdf_fdist_P(alpha,df1,df2);

  if (gsl_finite(val))
    printf("P is %lf\n",val);
  else
    printf("P with failed val is %lf\n",val);
  
  return 0;
  
}

