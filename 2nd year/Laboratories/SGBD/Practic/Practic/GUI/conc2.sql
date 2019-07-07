set transaction isolation level read uncommitted;

select *
from Supe
where cod_bucatar = 1;

set transaction isolation level read committed;
