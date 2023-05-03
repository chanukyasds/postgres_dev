DROP FUNCTION IF EXISTS return_records(integer[]);

CREATE OR REPLACE FUNCTION return_records(integer[])
RETURNS SETOF integer
AS '/extensions/return_records/return_records','return_records'
LANGUAGE C STRICT;

DROP FUNCTION IF EXISTS return_texts(integer);

CREATE OR REPLACE FUNCTION return_texts(integer)
RETURNS SETOF text
AS '/extensions/return_records/return_texts','return_texts'
LANGUAGE C STRICT;