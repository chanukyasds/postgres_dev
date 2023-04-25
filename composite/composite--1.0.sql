--DROP TYPE IF EXISTS custom_type;

--CREATE TYPE custom_type AS (a1 integer,a2 text,a3 integer[],a4 bigint);

DROP FUNCTION IF EXISTS composite(custom_type[]);

CREATE OR REPLACE FUNCTION composite(custom_type[])
RETURNS custom_type[]
AS '/extensions/composite/composite','composite'
LANGUAGE C STRICT;

/*
select  composite(ARRAY[
(201,'chanukya',ARRAY[35,90,65],0),
(202,'chaitanya',ARRAY[100,82,99],0),
(203,'kalyani',ARRAY[100,99,99,95],0),
(204,'ashok',ARRAY[100,78,99,82],0)
]::custom_type[]) ;
*/