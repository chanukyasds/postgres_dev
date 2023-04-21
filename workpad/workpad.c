#include "/usr/include/postgresql/14/server/postgres.h"
#include "/usr/include/postgresql/14/server/fmgr.h"
#include "/usr/include/postgresql/14/server/utils/lsyscache.h"
#include "/usr/include/postgresql/14/server/utils/array.h"
#include "/usr/include/postgresql/14/server/catalog/pg_type.h"
#include "stdio.h"

PG_MODULE_MAGIC;

Datum workpad(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(workpad);

Datum
workpad(PG_FUNCTION_ARGS)
{
    ArrayType *input_array = PG_GETARG_ARRAYTYPE_P(0);
    int new_element = PG_GETARG_INT32(1);
    int position = PG_GETARG_INT32(2);

    Oid elementype = ARR_ELEMTYPE(input_array);
    int16 elementwidth;
    bool elementtypebyval;
    char elementalignmentcode;
    Datum *elements;
    bool *nulls;
    int count;

    int *arr;
    int i,replaced_element;
    int found=0;

    ArrayType *output_array;

    get_typlenbyvalalign(elementype,&elementwidth,&elementtypebyval,&elementalignmentcode);

    deconstruct_array(input_array,elementype,elementwidth,elementtypebyval,elementalignmentcode,&elements,&nulls,&count);

    elog(NOTICE,"base type is %d", get_base_element_type(elementype));

    arr = malloc(sizeof(int *)*count+1);

    for (i=0;i<count;i++)
        arr[i]=elements[i];

    for (i=0;i<count;i++)
    {
        if (i==position)
        {
            replaced_element = arr[i];
            arr[i] = new_element;
            count++;
            found = 1;
            continue;
        }
        if (found==1)
        {
            arr[i]= arr[i]+replaced_element;
            replaced_element = arr[i]-replaced_element;
            arr[i]=arr[i]-replaced_element;
        }
    }

    elements = repalloc(elements,count);

    for (i=0;i<count;i++)
        elements[i]=Int64GetDatum(arr[i]);

    output_array = construct_array(elements,count,INT4OID,elementwidth,elementtypebyval,elementalignmentcode);

    construct_md_array

    deconstr

    PG_RETURN_ARRAYTYPE_P(output_array);

    

}




//get_array_type(elementype) gives pg_type.typearray 
// ARR_ELEMTYPE gives pg_type.oid
// get_fn_expr_argtype(fcinfo->flinfo, 0) gives pg_type.typearray

//get_typlen(elementype)) gives pg_type.typlen

// get_typlenbyval(elementtype,&elementwidth,&elementtypebyval); gives both width(length) and typebyval


// unused ----------------

//get_base_element_type(elementype) gives pg_type.typbasetype

/*
  * elems: array of Datum items to become the array contents
  * nulls: array of is-null flags (can be NULL if no nulls)
  * ndims: number of dimensions
  * dims: integer array with size of each dimension
  * lbs: integer array with lower bound of each dimension
  * elmtype, elmlen, elmbyval, elmalign: info for the datatype of the items
*/