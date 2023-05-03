#include "/usr/include/postgresql/14/server/postgres.h"
#include "/usr/include/postgresql/14/server/fmgr.h"
#include "/usr/include/postgresql/14/server/executor/executor.h"
#include "/usr/include/postgresql/14/server/utils/lsyscache.h"
#include "/usr/include/postgresql/14/server/utils/array.h"
#include "/usr/include/postgresql/14/server/utils/builtins.h"
#include "/usr/include/postgresql/14/server/catalog/pg_type.h"
#include "/usr/include/postgresql/14/server/access/tupmacs.h"
#include "/usr/include/postgresql/14/server/funcapi.h"

PG_MODULE_MAGIC;

union cust_union
{
    int val;
    char letter[1];
};

Datum return_texts(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(return_texts);

Datum return_texts(PG_FUNCTION_ARGS)
{
    int count = (int)PG_GETARG_INT64(0);

    FuncCallContext *funcctx;
    Datum each_row;

    if (SRF_IS_FIRSTCALL())
    {
        MemoryContext oldcontext;

        funcctx = SRF_FIRSTCALL_INIT();

        oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);

        funcctx->max_calls = count;
        funcctx->call_cntr = 0;

        MemoryContextSwitchTo(oldcontext);
    }

    funcctx = SRF_PERCALL_SETUP();

    if (funcctx->call_cntr < funcctx->max_calls)
    {

        union cust_union *u1;

        u1 = (union cust_union *)palloc(sizeof(union cust_union) * 1);

        u1->val = (int)65 + funcctx->call_cntr;

        char *result = u1->letter;

        each_row = CStringGetTextDatum(result);

        SRF_RETURN_NEXT(funcctx, each_row);
    }

    SRF_RETURN_DONE(funcctx);
}