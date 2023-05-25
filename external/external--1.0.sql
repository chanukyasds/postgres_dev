DROP FUNCTION IF EXISTS "external"(float8,float8,float8);

CREATE OR REPLACE FUNCTION "external"(float8,float8,float8)
RETURNS float8
AS '/extensions/external/external','external'
LANGUAGE C STRICT;