-- Создать, развернуть и протестировать 6 объектов SQL CLR:
-- 1) Определяемую пользователем скалярную функцию CLR,
create language plpython2u

create or replace function py_skal(arg dbo.people)
returns varchar(100)
as $$
	s1 = s2 = s3 = s4 = ""
	s1 = arg["name"]
	s2 = arg["surname"]
	s3 = arg["country"]
	s4 = arg["sex"]
	return s1 + " " +s2+ " " + s3 +" " + s4
$$ language plpython2u;

drop function  py_skal(arg dbo.people);

select dbo.people.*, py_skal(dbo.people.*) from dbo.people ;

-- 2) Пользовательскую агрегатную функцию CLR,


create or replace function mul(state int, arg int)
returns int
as $$
    return state * arg
$$ language plpython2u;

CREATE AGGREGATE my_agr(int)
(
    sfunc = mul,
    stype = int,
    initcond = 1
);
select * from dbo.artist where artistid < 1005;
select my_agr(age) from dbo.artist where artistid < 1005;

-- 3) Определяемую пользователем табличную функцию CLR,

create or replace function my_table_func(from_l int, to_l int)
returns table(name text, surname text, len int)
as $$
    p = plpy.execute("SELECT * FROM dbo.people")
    result = []
    for i in range(len(p)):
        s = p[i]["surname"]
        n = p[i]["name"]
        if (len(s) + len(n) > from_l and len(s) + len(n) < to_l):
            result.append({ "surname": s.rstrip(), "name": n.rstrip(), "len": len(s) + len(n)})
    return result
$$ language plpython2u;

select * from my_table_func(2,15)

-- 4) Хранимую процедуру CLR,

create or replace function my_proc( name1 text, name2 text)
returns void
as $$
	r = plpy.execute("SELECT * FROM " + name1)
	res = []
	count = []
	for i in range(len(r)):
		if (r[i]["age"] not in res):
		    res.append(r[i]["age"])
		    count.append(1)
		else:
		    count[res.index(r[i]["age"])] += 1
	for i in range(len(res)):
	    plpy.execute("update "+name2+" set count = "+str(count[i]) + " where age =" + str(res[i]))
$$ language plpython2u;
select * from dbo.new_people;
create table dbo.counts (age int, count int);
insert into dbo.counts (age, count) select age, count(*) from dbo.people group by age;
drop table dbo.counts
select * from dbo.counts
    order by age;
select * from my_proc('dbo.artist', 'dbo.counts');

-- 5) Триггер CLR,

create table dbo.deleted_people(
    name varchar(30) ,
    surname varchar(40));
)

create or replace function tr_before() returns trigger
as $$
	if TD["event"] == "DELETE":
	    a = str(TD["old"]["name"])
	    b = str(TD["old"]["surname"])
	    plpy.execute("insert into dbo.deleted_people(name, surname) values ('" + a + "', '" + b + "')")
	    return "OK"
	elif TD["event"] == "INSERT" or TD["event"] == "UPDATE":
	    a = plpy.execute("select * from dbo.deleted_people where name = '" + str(TD["new"]["name"] + "'"))
	    if (a):
	        return "SKIP"
		return "OK"
$$ language plpython2u;

create trigger trig3 before delete or update or insert on dbo.people
for each row execute procedure tr_before();



select * from dbo.deleted_people;

insert into dbo.people (artistid, name, surname) values (112321, 'Evans', 'balaal');
delete from dbo.people where artistid = 1006
select * from dbo.people where name = 'Evans'

-- 6) Определяемый пользователем тип данных CLR.

CREATE TYPE point;

CREATE OR REPLACE FUNCTION point_in ( s cstring )
RETURNS point AS
'type', 'point_in'
LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION point_out ( v point )
RETURNS cstring AS
'type', 'point_out'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point_recv ( p internal )
RETURNS point AS
'type', 'point_recv'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point_send ( v point )
RETURNS bytea AS
'type', 'point_send'
LANGUAGE C IMMUTABLE STRICT;

CREATE TYPE point
(
	internallength = 24,
	input = point_in,
	output = point_out,
	receive = point_recv,
	send = point_send
);

