#include <gsl/gsl_cdf.h>
#include <postgres.h>
#include <fmgr.h>

PG_MODULE_MAGIC;

Datum external(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(external);

Datum external(PG_FUNCTION_ARGS)

{
    const double alpha = PG_GETARG_FLOAT8(0);
    const double df1 = PG_GETARG_FLOAT8(1);
    const double df2 = PG_GETARG_FLOAT8(2);

    float Qinv = gsl_cdf_fdist_Qinv(alpha, df1, df2);
    float Pinv = gsl_cdf_fdist_Pinv(alpha, df1, df2);
    
    elog(NOTICE,"Qinv is %lf",Qinv);
    elog(NOTICE,"Pinv is %lf",Pinv);

    PG_RETURN_FLOAT8(Qinv);
}
