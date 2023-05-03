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

Datum return_texts(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(return_texts);

Datum return_texts(PG_FUNCTION_ARGS)
{
    int count = (int)PG_GETARG_INT64(0);

    FuncCallContext *funcctx;
    TupleDesc tupdesc;
    Datum each_row;


    if (SRF_IS_FIRSTCALL())
    {
        MemoryContext oldcontext;

        /* create a function context for cross-call persistence */
        funcctx = SRF_FIRSTCALL_INIT();

        /* switch to memory context appropriate for multiple function calls */
        oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);

        /* Build a tuple descriptor for our result type */
        tupdesc = CreateTemplateTupleDesc(1); // creating template
        TupleDescInitEntry(tupdesc, (AttrNumber)1, "a1", TEXTOID, -1, 0);
        tupdesc = BlessTupleDesc(tupdesc);

        /* allocate required values for funcctx */
        funcctx->max_calls = count;
        funcctx->call_cntr = 0;
        funcctx->tuple_desc = tupdesc;

        MemoryContextSwitchTo(oldcontext);
    }

    funcctx = SRF_PERCALL_SETUP();

    if (funcctx->call_cntr < funcctx->max_calls)
    {
        /* index is passed as funcctx->call_cntr because its starts from 0 and
        increments everytime by SRF_RETURN_NEXT */

        char result[5] = "HELLO";

        each_row =  CStringGetTextDatum(result);

        SRF_RETURN_NEXT(funcctx, each_row);
    }

    SRF_RETURN_DONE(funcctx);
}