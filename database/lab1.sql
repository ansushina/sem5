create database myStore;
go

select * from sys.databases
where name = 'myStore';

use myStore;
go

create schema ODS_1; -- Сюда загружаются данные из источника "Поставки"
create schema ODS_2; -- Сюда загружаются данные из источника "Продажи"
create schema ODS_3; -- Сюда загружаются данные из источника "Отчетность"
go


-- Информация о поставке
create table ODS_1.Delivery(
    del_code varchar(10) NOT NULL PRIMARY KEY,
    del_date date,
    del_description nvarchar(1000),
    del_destination varchar(10),
    del_company varchar(10)
);
insert into ODS_1.Delivery(del_code, del_date, del_description, del_destination, del_company) values('RFFTDGEOOT', CAST('16 Sep 2019' AS date), 'no comments', 'TRDHSRQNDR', 'ASRHNAEWQP');
insert into ODS_1.Delivery(del_code, del_date, del_description, del_destination, del_company) values('RTDFEFFRAD', CAST('29 Oct 2019' AS date), 'no comments', 'TRDHSRQNDR', 'YTDNRSDLPY');
insert into ODS_1.Delivery(del_code, del_date, del_description, del_destination, del_company) values('RRRTDRAEWW', CAST('10 Aug 2019' AS date), 'no comments', 'TRDHSRQNDR', 'ATDGRMIPER');
insert into ODS_1.Delivery(del_code, del_date, del_description, del_destination, del_company) values('RTDTTSRWJJ', CAST('10 Aug 2019' AS date), 'no comments', 'ERTDBARDTW', 'ASRHNAEWQP');
insert into ODS_1.Delivery(del_code, del_date, del_description, del_destination, del_company) values('PRTGRRTETT', CAST('23 Aug 2019' AS date), 'no comments', 'ERTDBARDTW', 'ASRHNAEWQP');

select * from ODS_1.Delivery;


-- Информация о складах компании
create table ODS_1.StoreRooms( 
    store_code varchar(10) NOT NULL,
    line1 nvarchar(50),
    line2 nvarchar(50),
    city nvarchar(50),
    state nvarchar(50),
    ZIP nvarchar(10),
    country nvarchar(50),
    phone nvarchar(10)
);
insert into ODS_1.StoreRooms (store_code, line1, line2, city, state, ZIP, country, phone) values('TRDHSRQNDR', '700 Carpenters Crossing', 'Ste 14563829', 'Folcroft', 'Pennsylvania', '5643271643', 'USA', '4845463853');
insert into ODS_1.StoreRooms (store_code, line1, line2, city, state, ZIP, country, phone) values('WERTSDREMT', '300 Carpenters Circle', 'Ste 65784b', 'Wilmington', 'Delaware', '5674321749', 'USA', '4845454321');
insert into ODS_1.StoreRooms (store_code, line1, line2, city, state, ZIP, country, phone) values('ERTDBARDTW', '7 Lewis Circle', 'Ste 4537282', 'Folcroft', 'Pennsylvania', '0945632715', 'USA', '4845460000');
insert into ODS_1.StoreRooms (store_code, line1, line2, city, state, ZIP, country, phone) values('ARDFEWQJTL', '10 Lewis Circle', 'Ste 36473823', 'Wilmington', 'Delaware', '0976443621', 'USA', '4845463454');
insert into ODS_1.StoreRooms (store_code, line1, line2, city, state, ZIP, country, phone) values('DTGERVATNY', '450 Carpenters Crossing', 'Ste 3536238290', 'Folcroft', 'Pennsylvania', '5564377582', 'USA', '4845460110');

select * from ODS_1.StoreRooms;


-- Информация о поставщиках
create table ODS_1.Company(
    store_code varchar(10) NOT NULL,
    name nvarchar(50),
    inn varchar(10),
    address nvarchar(100),
    agent nvarchar(50),
);

insert into ODS_1.Company(store_code, name, inn, address, agent) values('ASRHNAEWQP', 'SuperComp', '1235431567', 'myCountry, myLine', 'Ivanov Ivan');
insert into ODS_1.Company(store_code, name, inn, address, agent) values('HYTSLPODCT', 'newDeliveryComp', '3456324569', 'myCountry1, myLine1', 'Perov Ivan');
insert into ODS_1.Company(store_code, name, inn, address, agent) values('YTDNRSDLPY', 'oldDeliveryComp', '6543786531', 'myCountry2, myLine2', 'Petrov Peter');
insert into ODS_1.Company(store_code, name, inn, address, agent) values('ATDGRMIPER', 'anotherDeliveryComp', '8547832547', 'myCountry3, myLine3', 'Smirnov Alexey');
insert into ODS_1.Company(store_code, name, inn, address, agent) values('YTWRDNAPTQ', 'SuperComp', '5954632163', 'myCountry4, myLine4', 'Ivanova Inna');

select * from ODS_1.Company;