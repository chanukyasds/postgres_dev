#include "postgresql/14/server/postgres.h"
#include <string.h>
#include "fmgr.h"
#include "postgresql/14/server/utils/geo_decls.h"
#include <stdio.h>
#include "postgresql/14/server/utils/array.h"



PG_MODULE_MAGIC;

Datum array_rotate_left(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(array_rotate_left);

Datum
array_rotate_left(PG_FUNCTION_ARGS)
{
    ExpandedArrayHeader *eah=PG_GETARG_ARRAYTYPE_P(0);

    int32 rotation_cycle=PG_GETARG_INT32(1);

    int32 array_length = eah->nelems;

    int32 i,j,temp;

    Datum *data_array = eah->dvalues;
    
    

    for (i=0;i<rotation_cycle;i++)
    {    
        temp=data_array[0]; // each time arr[0] will get changed because of shifting 
        for(j=0;j<array_length;j++)
            data_array[j] = data_array[j+1];
        data_array[array_length-1]=temp; // appending one by one

    }
    
    PG_RETURN_ARRAYTYPE_P(data_array);

    return 0;

}