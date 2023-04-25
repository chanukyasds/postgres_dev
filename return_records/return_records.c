#include "/usr/include/postgresql/14/server/postgres.h"
#include "/usr/include/postgresql/14/server/fmgr.h"
#include "/usr/include/postgresql/14/server/executor/executor.h"
#include "/usr/include/postgresql/14/server/utils/lsyscache.h"
#include "/usr/include/postgresql/14/server/utils/array.h"
#include "/usr/include/postgresql/14/server/catalog/pg_type.h"
#include "/usr/include/postgresql/14/server/access/tupmacs.h"
#include "/usr/include/postgresql/14/server/funcapi.h"
#include "stdio.h"
#include "stddef.h"


PG_MODULE_MAGIC;

Datum return_records(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(return_records);

Datum
return_records(PG_FUNCTION_ARGS)
{
    ArrayType *input_array = PG_GETARG_ARRAYTYPE_P(0);
    Oid elementType = ARR_ELEMTYPE(input_array);
    
    int16 elementWidth;
    bool elementTypeByVal;
    char elementAlignmentCode;
    bool *nulls;
    Datum *elements;
    int count;

    int i;
    FuncCallContext  *funcctx;

    funcctx = SRF_PERCALL_SETUP();


    get_typlenbyvalalign(elementType,&elementWidth,&elementTypeByVal,&elementAlignmentCode);
    deconstruct_array(input_array,elementType,elementWidth,elementTypeByVal,elementAlignmentCode,&elements,&nulls,&count);


    
    

    

}