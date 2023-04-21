#include "/usr/include/postgresql/14/server/postgres.h"
#include "/usr/include/postgresql/14/server/fmgr.h"
#include "/usr/include/postgresql/14/server/executor/executor.h"  
#include "/usr/include/postgresql/14/server/utils/lsyscache.h"
#include "/usr/include/postgresql/14/server/utils/array.h"
#include "/usr/include/postgresql/14/server/catalog/pg_type.h"
#include "/usr/include/postgresql/14/server/access/tupmacs.h"
#include "stdio.h"
#include "stddef.h"

PG_MODULE_MAGIC;

Datum composite(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(composite);

Datum
composite(PG_FUNCTION_ARGS)
{
    ArrayType *input_array = PG_GETARG_ARRAYTYPE_P(0);

    Oid elementtype = ARR_ELEMTYPE(input_array);

    int16 elementwidth;
    bool elementtypebyval;
    char elementalignmentcode;
    Datum *elements;
    bool *nulls;
    int count;

    int i,j;
    HeapTupleHeader row_header;
    Datum sub_dt;
    ArrayType *sub_arr;
    int *irr;
    int sum=0;
    int *len;
    Datum res;

    ArrayType *output_array;


    int ndims = ARR_NDIM(input_array);
    int *dims = ARR_DIMS(input_array);
    int *lbs = ARR_LBOUND(input_array);

    get_typlenbyvalalign(elementtype,&elementwidth,&elementtypebyval,&elementalignmentcode);

    deconstruct_array(input_array,elementtype,elementwidth,elementtypebyval,elementalignmentcode,&elements,&nulls,&count);




    for (i=0;i<count;i++)
    {

        sum=0;

        row_header = DatumGetHeapTupleHeader(elements[i]);
        bool isnull;

        sub_dt = GetAttributeByName(row_header, "a3", &isnull);

        sub_arr = DatumGetArrayTypeP(sub_dt);

        irr = (int *)ARR_DATA_PTR(sub_arr);

        len = ARR_DIMS(sub_arr);

        for (j=0;j<len[0];j++)
            sum=sum+irr[j];

        elog(NOTICE,"sum is %d",sum);

        bool isanothernull;

        res = GetAttributeByName(row_header,"a4",&isanothernull);

        res = Int64GetDatum(sum);

        elog(NOTICE,"res is %d",res);
        
    }


    output_array = construct_array(elements, count,2276, elementwidth, elementtypebyval, elementalignmentcode);

   
    // Datum dt = GetAttributeByName(t,"a2",&isnull);

    // elog(NOTICE,"%s",text_to_cstring(dt));
   
    
    

    // elog(NOTICE,"%d",tt[0]);

    // ArrayType *sub_array = DatumGetArrayTypeP(dt);

    // Datum *arr = (Datum *) ARR_DATA_PTR(sub_array);
    
    // elog(NOTICE,"element is %ld",(arr[0]));

    

    //ArrayType *sub_array =  DatumGetArrayTypeP(dt);



    /*

    Oid sub_elementtype = ARR_ELEMTYPE(sub_array);

    int16 sub_elementwidth;
    bool sub_elementtypebyval;
    char sub_elementalignmentcode;
    Datum *sub_elements;
    bool *sub_nulls;
    int sub_count;

    get_typlenbyvalalign(sub_elementtype,&sub_elementwidth,&sub_elementtypebyval,&sub_elementalignmentcode);

    deconstruct_array(sub_array,sub_elementtype,sub_elementwidth,sub_elementtypebyval,sub_elementalignmentcode,&sub_elements,&sub_nulls,&sub_count);

    elog(NOTICE,"element is %d",sub_elements[0]);
 
    // ArrayType *sub_array = DatumGetArrayTypeP(marks);

    //elog(NOTICE,"ELEMENT VALUE is %d",Int64GetDatum(elements[1]));

    //elog(NOTICE,"count is %d",count);

    */

    PG_RETURN_ARRAYTYPE_P(output_array);
}
