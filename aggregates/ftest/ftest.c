#include <postgres.h>
#include <fmgr.h>
#include <utils/array.h>
#include <catalog/pg_type.h>
#include <utils/lsyscache.h>
#include <math.h>
#include <string.h>
#include <common/int.h>
#include <utils/builtins.h>
#include <utils/typcache.h>
#include <funcapi.h>
#include <utils/numeric.h>
#include <executor/spi.h>


struct sample_data
{
    int *data;    // data array of sample
    int size;     // size of sample
    int df;       // degrees of freedom
    float mean;     // mean of sample
    float variance; // variance of sample
} sd;

struct ftest_data
{
    long double f_value;
    long double f_right_tail;
    long double f_left_tail;
    long double f_two_tail_1;
    long double f_two_tail_2;
    long double p_right_tail;
    long double p_left_tail;
    long double p_two_tail;
} fd;

struct sample_data *sample1;
struct sample_data *sample2;

struct ftest_data *ftest_result;

float8 alpha;

PG_MODULE_MAGIC;

Datum ftest_sfunc(PG_FUNCTION_ARGS);
Datum ftest_ffunc(PG_FUNCTION_ARGS);

void calculate_mean(struct sample_data *);
void calculate_variance(struct sample_data *);
void calculate_fvalues(struct ftest_data *);
long double get_ftable_values(float8, int, int);
void push_ftest_results();

PG_FUNCTION_INFO_V1(ftest_sfunc);
PG_FUNCTION_INFO_V1(ftest_ffunc);

void calculate_mean(struct sample_data *sample)
{
    int i;
    int mean;
    int sum = 0;
    int size = sample->size;

    for (i = 0; i < size; i++)
        sum = sum + sample->data[i];

    mean = sum / size;
    sample->mean = mean;
}

void calculate_variance(struct sample_data *sample)
{
    int i;
    int mean = sample->mean;
    int size = sample->size;
    int each_dev;
    int sum_of_dev_sq = 0;
    int variance;

    for (i = 0; i < size; i++)
    {
        each_dev = (sample->data[i] - mean);
        sum_of_dev_sq = sum_of_dev_sq + (each_dev * each_dev);
    }

    variance = (sum_of_dev_sq / (size - 1));
    sample->variance = variance;
}

long double get_ftable_values(float8 alpha, int df1, int df2)
{
    long double value = 0.0;
    SPITupleTable *tupTable;
    char query[200];
    TupleDesc tupdesc;
    HeapTuple tuple;
    bool isnull;
    pg_sprintf(query, "SELECT n%d::float8 FROM ftable WHERE alpha=%f AND dn = '%d';", df1, alpha, df2);
    elog(NOTICE,"%s",query);
    SPI_connect();
    SPI_exec(query, 0);
    tupTable = SPI_tuptable;
    tupdesc = tupTable->tupdesc;
    tuple = tupTable->vals[0];
    value = SPI_getbinval(tuple, tupdesc, 1, &isnull);
    SPI_finish();
    return value;
}

void calculate_fvalues(struct ftest_data *ftest)
{
    ftest->f_right_tail = get_ftable_values(alpha, sample1->df, sample2->df);
    ftest->f_left_tail = 1 / ftest->f_right_tail;
    ftest->f_two_tail_2 = get_ftable_values(alpha / 2, sample1->df, sample2->df);
    ftest->f_two_tail_1 = 1 / ftest->f_two_tail_2 ;
}

void push_ftest_results()
{

    // elog(NOTICE,"Mean of sample->1 is %d",sample1->mean);
    // elog(NOTICE,"Mean of sample->2 is %d",sample2->mean);

    // elog(NOTICE,"variance of sample->1 is %d",sample1->variance);
    // elog(NOTICE,"variance of sample->2 is %d",sample2->variance);

    // elog(NOTICE,"observations of sample->1 is %d",sample1->size);
    // elog(NOTICE,"observations of sample->2 is %d",sample2->size);

    // elog(NOTICE,"df of sample->1 is %d",sample1->df);
    // elog(NOTICE,"df of sample->2 is %d",sample2->df);

    // elog(NOTICE,"F value  is %f",ftest_result->f_value);

    // elog(NOTICE,"F right tail is %f",ftest_result->f_right_tail);

    // elog(NOTICE,"F left tail is %f",ftest_result->f_left_tail);

   
    // elog(NOTICE,"F two tail 1 is %f",ftest_result->f_two_tail_1);
    // elog(NOTICE,"F two tail 2 is %f",ftest_result->f_two_tail_2);

    
    elog(NOTICE,"commented");

    // char query[200];
    // SPI_connect();
    // pg_sprintf(query, "INSERT INTO ftest_result VALUES('Mean',%d,%d) RETURNING 1;",sample1->mean,sample2->mean);
    // SPI_exec(query, 0);
    // pg_sprintf(query, "INSERT INTO ftest_result VALUES('Variance',%d,%d) RETURNING 1;",sample1->variance,sample2->variance);
    // SPI_exec(query, 0);
    // pg_sprintf(query, "INSERT INTO ftest_result VALUES('Observations',%d,%d) RETURNING 1;",sample1->size,sample2->size);
    // SPI_exec(query, 0);
    // pg_sprintf(query, "INSERT INTO ftest_result VALUES('Degrees Of Freedom',%d,%d) RETURNING 1;",sample1->df,sample2->df);
    // SPI_exec(query, 0);
    // pg_sprintf(query, "INSERT INTO ftest_result(method_name,sample1) VALUES('F Value',%f) RETURNING 1;",ftest_result->f_value);
    // SPI_exec(query, 0);
    // pg_sprintf(query, "INSERT INTO ftest_result(method_name,sample1) VALUES('F Right Tail',%.f) RETURNING 1;",ftest_result->f_right_tail);
    // SPI_exec(query, 0);
    // pg_sprintf(query, "INSERT INTO ftest_result(method_name,sample1) VALUES('F Left Tail',%f) RETURNING 1;",ftest_result->f_left_tail);
    // SPI_exec(query, 0);
    // pg_sprintf(query, "INSERT INTO ftest_result VALUES('F Two Tail',%f,%f) RETURNING 1;",ftest_result->f_two_tail_1,ftest_result->f_two_tail_2);
    // SPI_exec(query, 0);
    // SPI_finish();
}

Datum ftest_sfunc(PG_FUNCTION_ARGS)
{
    ArrayBuildState *state;
    ArrayType *arr;

    MemoryContext aggcontext;
    Oid arg_type_1 = get_fn_expr_argtype(fcinfo->flinfo, 1);
    Oid arg_type_2 = get_fn_expr_argtype(fcinfo->flinfo, 2);
    Datum data[2];

    if (arg_type_1 == InvalidOid || arg_type_2 == InvalidOid)
        elog(ERROR, "Invalid paramter values");

    if (arg_type_1 != arg_type_2)
        elog(ERROR, "both types are not equal");

    if (!AggCheckCallContext(fcinfo, &aggcontext))
        elog(ERROR, "ftest_sfunc called in non-aggregate context");

    if (PG_ARGISNULL(0))
    {
        state = initArrayResult(INT4ARRAYOID, aggcontext, false);
        alpha = PG_GETARG_FLOAT8(3);
    }
    else
        state = (ArrayBuildState *)PG_GETARG_POINTER(0);

    data[0] = PG_ARGISNULL(1) ? (Datum)0 : (int)PG_GETARG_DATUM(1);

    data[1] = PG_ARGISNULL(2) ? (Datum)0 : (int)PG_GETARG_DATUM(2);

    arr = construct_array(data, 2, INT4OID, 4, true, 'i');

    state = accumArrayResult(state, PointerGetDatum(arr), false, INT4ARRAYOID, aggcontext);

    PG_RETURN_POINTER(state);
}

Datum ftest_ffunc(PG_FUNCTION_ARGS)
{
    ArrayBuildState *state;
    ArrayType *array;
    Oid elementType;
    int16 elementWidth;
    bool elementTypeByval;
    char elementAlignmentCode;
    Datum *elements;
    bool *nulls;
    int count;

    int *inner_arr;
    int i;

    sample1 = (struct sample_data *)palloc(sizeof(struct sample_data *));
    sample2 = (struct sample_data *)palloc(sizeof(struct sample_data *));

    ftest_result = (struct ftest_data *)palloc(sizeof(struct ftest_data *));

    state = PG_ARGISNULL(0) ? NULL : (ArrayBuildState *)PG_GETARG_POINTER(0);

    if (state == NULL)
        PG_RETURN_NULL();

    array = (ArrayType *)makeArrayResult(state, CurrentMemoryContext);
    elementType = ARR_ELEMTYPE(array);

    get_typlenbyvalalign(elementType, &elementWidth, &elementTypeByval, &elementAlignmentCode);

    deconstruct_array(array, elementType, elementWidth, elementTypeByval, elementAlignmentCode,
                      &elements, &nulls, &count);

    sample1->data = (int *)palloc(sizeof(int *) * count);
    sample2->data = (int *)palloc(sizeof(int *) * count);

    sample1->size = count;
    sample2->size = count;

    sample1->df = count - 1;
    sample2->df = count - 1;

    for (i = 0; i < count; i++)
    {
        inner_arr = (int *)ARR_DATA_PTR(DatumGetArrayTypeP(elements[i]));
        sample1->data[i] = inner_arr[0];
        sample2->data[i] = inner_arr[1];
    }

    calculate_mean(sample1);
    calculate_mean(sample2);

    calculate_variance(sample1);
    calculate_variance(sample2);

    ftest_result->f_value = (float)sample1->variance / sample2->variance;

    calculate_fvalues(ftest_result);

    push_ftest_results();

    PG_RETURN_INT32(1);

}