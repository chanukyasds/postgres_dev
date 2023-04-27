#include "/usr/include/postgresql/14/server/postgres.h"
#include "/usr/include/postgresql/14/server/fmgr.h"
#include "/usr/include/postgresql/14/server/executor/executor.h"
#include "/usr/include/postgresql/14/server/utils/lsyscache.h"
#include "/usr/include/postgresql/14/server/utils/array.h"
#include "/usr/include/postgresql/14/server/catalog/pg_type.h"
#include "/usr/include/postgresql/14/server/utils/builtins.h"
#include "/usr/include/postgresql/14/server/access/tupmacs.h"
#include "/usr/include/postgresql/14/server/funcapi.h"
#include "stdio.h"

PG_MODULE_MAGIC;

Datum split_composite(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(split_composite);

Datum split_composite(PG_FUNCTION_ARGS)
{
    ArrayType *input_array = PG_GETARG_ARRAYTYPE_P(0);
    Oid elementType = ARR_ELEMTYPE(input_array);

    int16 elementWidth;
    bool elementTypeByVal;
    char elementAlignmentCode;
    Datum *elements;
    bool *nulls;
    int count;

    int i;
    FuncCallContext *funcctx;
    TupleDesc tupDesc;
    HeapTupleHeader tupHeader;
    Datum *fields;
    HeapTuple tuple;
    Datum each_row;

    get_typlenbyvalalign(elementType, &elementWidth, &elementTypeByVal, &elementAlignmentCode);

    deconstruct_array(input_array, elementType, elementWidth, elementTypeByVal, elementAlignmentCode, &elements, &nulls, &count);

    if (SRF_IS_FIRSTCALL())
    {
        MemoryContext oldcontext;

        funcctx = SRF_FIRSTCALL_INIT();

        oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);

        tupDesc = CreateTemplateTupleDesc(4);
        TupleDescInitEntry(tupDesc, (AttrNumber)1, "a1", INT4OID, -1, 0);
        TupleDescInitEntry(tupDesc, (AttrNumber)2, "a2", TEXTOID, -1, 0);
        TupleDescInitEntry(tupDesc, (AttrNumber)3, "a3", INT4ARRAYOID, -1, 0);
        TupleDescInitEntry(tupDesc, (AttrNumber)4, "a4", INT4OID, -1, 0);
        tupDesc = BlessTupleDesc(tupDesc);

        funcctx->max_calls = count;
        funcctx->call_cntr = 0;
        funcctx->tuple_desc = tupDesc;

        MemoryContextSwitchTo(oldcontext);
    }

    funcctx = SRF_PERCALL_SETUP();

    

    if (funcctx->call_cntr < funcctx->max_calls)
    {
        fields = palloc(sizeof(Datum *)*4);

        bool isnull1,isnull2,isnull3,isnull4,tupnull;

        i = (int)funcctx->call_cntr;

        tupHeader = DatumGetHeapTupleHeader(elements[i]);

        fields[0] = GetAttributeByName(tupHeader,"a1",&isnull1);
        fields[1] = GetAttributeByName(tupHeader,"a2",&isnull2);
        fields[2] = GetAttributeByName(tupHeader,"a3",&isnull3);
        fields[3] = GetAttributeByName(tupHeader,"a4",&isnull4);

        tuple = heap_form_tuple(funcctx->tuple_desc,fields,&tupnull);

        each_row = HeapTupleGetDatum(tuple);

        SRF_RETURN_NEXT(funcctx,each_row);
    }

    SRF_RETURN_DONE(funcctx);

}