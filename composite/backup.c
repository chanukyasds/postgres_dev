

// Datum *arr_vals;

// arr_vals = palloc(sizeof(Datum *)*3);

// arr_vals[0]=(100);
// arr_vals[1]=(100);
// arr_vals[2]=(100);

// output_datums[0] = GetAttributeByNum(row_header, 1, &isnull1);
// output_datums[1] = GetAttributeByNum(row_header, 2, &isnull2);
// //output_datums[2] = GetAttributeByNum(row_header, 3, &isnull3);
// output_datums[2] = PointerGetDatum(construct_array(arr_vals,3,INT8OID,8,true,'i'));
// output_datums[3] = 800;



// Above is for manual data providing into tuple datum

// heap_modify_tuple_by_cols(elements[0],resultTupleDesc,4,rep,dt,&isnull);

// elog(INFO,"  %d",resultTupleDesc->natts);

// int nnn = tdesc->natts;

// get_call_result_type()

// DatumGetHeapTupleHeader();

// heap_copy_tuple_as_datum

// heap_modify_tuple_by_cols()

// Datum dt = GetAttributeByName(t,"a2",&isnull);

// elog(NOTICE,"%s",text_to_cstring(dt));

// elog(NOTICE,"%d",tt[0]);

// ArrayType *sub_array = DatumGetArrayTypeP(dt);

// Datum *arr = (Datum *) ARR_DATA_PTR(sub_array);

// elog(NOTICE,"element is %ld",(arr[0]));

// ArrayType *sub_array =  DatumGetArrayTypeP(dt);

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