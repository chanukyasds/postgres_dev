drop extension composite;
create extension composite;

select workpad(ARRAY[7,2,3,4,5,6,12,24,67,15,29],9,3);

select workpad(ARRAY[1,2,3,4,5,6,7,8],9,3);

select oid,typname,typlen,typbyval,typtype,typcategory,typelem,typarray,typalign from pg_type where oid = 23;

select * from pg_type where typname = 'custom_type';

select ARRAY[ARRAY[1,2,3],ARRAY[4,5,6]];

select workpad(ARRAY[ARRAY[1,2,3],ARRAY[4,5,6],ARRAY[9,8,7],ARRAY[10,32,14]],9,3);

DROP TYPE IF EXISTS custom_type;

CREATE TYPE custom_type AS (a1 integer,a2 text,a3 integer[],a4 bigint);

select composite(ARRAY[(201,'chanukya',ARRAY[35,90,65],0),(202,'chaitanya',ARRAY[95,82,99],0)]::custom_type[])

SELECT ARRAY[(201,'chanukya',ARRAY[10,20,30],0),(201,'chanukya',ARRAY[10,20,30],0)]::custom_type[]

select * from pg_available_extensions order by 1;


select (201,'chanukya',ARRAY[35,90,65],0)::custom_type

