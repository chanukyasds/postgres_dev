DROP FUNCTION IF EXISTS return_texts(integer);

CREATE OR REPLACE FUNCTION return_texts(integer)
RETURNS SETOF text
AS '/extensions/return_texts/return_texts','return_texts'
LANGUAGE C STRICT;