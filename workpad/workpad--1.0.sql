DROP FUNCTION IF EXISTS workpad(integer[],integer,integer);

CREATE OR REPLACE FUNCTION workpad(integer[],integer,integer)
RETURNS integer[]
AS '/extensions/workpad/workpad','workpad'
LANGUAGE C STRICT;