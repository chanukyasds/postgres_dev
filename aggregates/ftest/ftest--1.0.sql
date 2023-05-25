
DROP FUNCTION IF EXISTS ftest_sfunc(internal,anynonarray,anynonarray,float8);

CREATE OR REPLACE FUNCTION 
ftest_sfunc(internal,anynonarray,anynonarray,float8)
RETURNS internal
AS '/extensions/aggregates/ftest/ftest', 'ftest_sfunc'
LANGUAGE c IMMUTABLE;


DROP FUNCTION IF EXISTS ftest_ffunc(internal,anynonarray,anynonarray,float8);

CREATE OR REPLACE FUNCTION 
ftest_ffunc(internal,anynonarray,anynonarray,float8)
RETURNS integer
AS '/extensions/aggregates/ftest/ftest', 'ftest_ffunc'
LANGUAGE c IMMUTABLE;

DROP AGGREGATE IF EXISTS ftest(anynonarray,anynonarray,float8);

CREATE OR REPLACE AGGREGATE ftest(anynonarray,anynonarray,float8)(
        SFUNC=ftest_sfunc,
        STYPE=internal,
        FINALFUNC=ftest_ffunc,
        FINALFUNC_EXTRA
);

