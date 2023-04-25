DROP FUNCTION IF EXISTS array_to_records(integer[]);

CREATE OR REPLACE FUNCTION array_to_records(integer[])
RETURNS SETOF integer
AS '/extensions/return_records/return_records','return_records'
LANGUAGE C STRICT;