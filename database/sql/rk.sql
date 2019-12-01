-- Рубежный контроль No2. Вариант 1
-- Задание 1 (4 балла)
-- Создать базу данных RK2. Создать в ней структуру, соответствующую
-- указанной на ER-диаграмме. Заполнить таблицы тестовыми значениями (не
-- менее 10 в каждой таблице).
create database rk2;

create  table Worker (
    id int not null primary key,
    team_id int,
    post varchar(30),
    fio varchar(30),
    salary int
);

create table  Team (
    id int not null primary key,
    title varchar(30),
    phone varchar(15),
    manager_id int
);

create table medicament (
    id int not null  primary key,
    title varchar(30),
    description varchar(500),
    price int
);

create table WM (
    id int not null primary key,
    worker_id int,
    med_id int
);

insert into Worker (id, team_id, post, fio, salary) values (1, 1, 'инженер', 'Вася Пупкин', 50000);
insert into Worker (id, team_id, post, fio, salary) values (2, 1, 'программист', 'Вася Ступкин', 67000);
insert into Worker (id, team_id, post, fio, salary) values (3, 1, 'менеджер', 'Костя Иванов', 100000);
insert into Worker (id, team_id, post, fio, salary) values (4, 2, 'тим лид', 'Вова Бакулев', 75000);
insert into Worker (id, team_id, post, fio, salary) values (5, 3, 'инженер', 'Мария Иванова', 55000);
insert into Worker (id, team_id, post, fio, salary) values (6, 3, 'тим лид', 'Дима Данилов', 70000);
insert into Worker (id, team_id, post, fio, salary) values (7, 7, 'инженер', 'Лиза Кирова', 40000);
insert into Worker (id, team_id, post, fio, salary) values (8, 7, 'менеджер', 'Маша Романова', 120000);
insert into Worker (id, team_id, post, fio, salary) values (9, 10, 'инженер', 'Гриша Будкин', 57000);
insert into Worker (id, team_id, post, fio, salary) values (10,10, 'программист', 'Настя Полякова', 62000);

insert into Team (id, title, phone, manager_id) VALUES (1,'планирования', '87898888899', 3);
insert into Team (id, title, phone, manager_id) VALUES (2,'расчета', '87898821299', null);
insert into Team (id, title, phone, manager_id) VALUES (3,'разработки', '87833338899', 6);
insert into Team (id, title, phone, manager_id) VALUES (4,'kek', '87899999899', null);
insert into Team (id, title, phone, manager_id) VALUES (5,'меджмента', '87822888899', null);
insert into Team (id, title, phone, manager_id) VALUES (6,'бугалтерия', '87898238899', null);
insert into Team (id, title, phone, manager_id) VALUES (7,'uou', '87822338899', 8);
insert into Team (id, title, phone, manager_id) VALUES (8,'oio', '37891811199', null);
insert into Team (id, title, phone, manager_id) VALUES (9,'non', '878982118899', null);
insert into Team (id, title, phone, manager_id) VALUES (10,'lol', '87892188349', 10);

insert into medicament (id, title, description, price) VALUES (1,'антиленин', 'a', 232);
insert into medicament (id, title, description, price) VALUES (2,'мотиватор верде', 'b', 300);
insert into medicament (id, title, description, price) VALUES (3,'расслабительное', 'c', 450);
insert into medicament (id, title, description, price) VALUES (4,'анальгин', 'd', 60);
insert into medicament (id, title, description, price) VALUES (5,'аскорбинка', 'k', 35);
insert into medicament (id, title, description, price) VALUES (6,'аспирин', 'l', 70);
insert into medicament (id, title, description, price) VALUES (7,'ношпа', 'm', 800);
insert into medicament (id, title, description, price) VALUES (8,'активированный уголь', 'n', 50);
insert into medicament (id, title, description, price) VALUES (9,'нурафен', 'o', 250);
insert into medicament (id, title, description, price) VALUES (10,'глазолин', 'p', 100);

insert into WM (id, worker_id, med_id) VALUES (1, 1, 1);
insert into WM (id, worker_id, med_id) VALUES (2, 1, 2);
insert into WM (id, worker_id, med_id) VALUES (3, 5, 10);
insert into WM (id, worker_id, med_id) VALUES (4, 4, 2);
insert into WM (id, worker_id, med_id) VALUES (5, 2, 5);
insert into WM (id, worker_id, med_id) VALUES (6, 3, 8);
insert into WM (id, worker_id, med_id) VALUES (7, 3, 4);
insert into WM (id, worker_id, med_id) VALUES (8, 6, 3);
insert into WM (id, worker_id, med_id) VALUES (9, 8, 9);
insert into WM (id, worker_id, med_id) VALUES (10, 8, 8);

alter table Worker add constraint fk_WT foreign key (team_id) references team (id);
alter table Team add constraint  fk_TManager foreign key (manager_id) references  Worker (id);
alter table WM add constraint  fk_WM_worker foreign key (worker_id) references Worker (id);
alter table WM add constraint  fk_WM_med foreign key (med_id) references  medicament (id);

select * from Worker;
select * from Team;
select * from medicament;
select  * from WM;

-- Задание 2 (6 баллов)
-- Написать к разработанной базе данных 3 запроса, в комментарии указать, что
-- этот запрос делает:
-- 1) Инструкцию SELECT, использующую простое выражение CASE

-- добавляется столбец обозначающий финансовое положение сотрудников. Среди обычных зарплат выделяется три,
-- для которых значения столбца особенные

select fio, post, salary,
       case salary
            when 100000 then 'rich'
            when 70000 then 'middle'
            when 40000 then 'poor'
            else 'normal'
        end as p
from Worker;

-- 2) Инструкцию, использующую оконную функцию

-- Добавляем 5 столбцов, которыре показывают среднюю зарплату для всех, среднюю по посту,
-- минимальную по посту, максимальную по посту, макисмлаьную для всех

SELECT fio,post,salary,
       avg(salary) over() as AvgbyAll,
       AVG(salary) OVER(partition by post) AS AvgByPost,
       MIN(salary) OVER(partition by post) AS MinByPost,
       MAX(salary) OVER(partition by post) AS MaxByPost,
       Max(salary) over() as MaxByAll
FROM Worker;

-- 3) Инструкцию SELECT, консолидирующую данные с помощью
-- предложения GROUP BY и предложения HAVING

-- Выводит сотрудников, которым выписано 2 или более медикамента

select w.fio, w.id, salary, count(*)
from Worker w join WM on worker_id = w.id
group by w.fio, w.id, salary having count(*) >= 2;


-- Задание 3 (10 баллов)
-- Создать хранимую процедуру с двумя входными параметрами – имя базы
-- данных и имя таблицы, которая выводит сведения об индексах указанной
-- таблицы в указанной базе данных.

create procedure my_proc(dbname varchar(30), tablename varchar(30))
as
    $$
    begin
    SELECT
      class1.relname, i.*
    FROM
      pg_index i
      join pg_class class1 on class1.oid = i.indexrelid
      join pg_class class2 on class2.oid = i.indrelid
    WHERE
      class2.relname = tablename;
    end;
    $$
language 'plpgsql';

drop procedure my_proc(dbname varchar, tablename varchar);

call my_proc('', 'team');