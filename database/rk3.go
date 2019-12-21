package main

import (
	"database/sql"
	"fmt"
	_ "github.com/lib/pq"
)

func teams_with_late() {
	connStr := "user=nastya password=namtaehyun99 dbname=rk3 sslmode=disable"
	db, err := sql.Open("postgres", connStr)
	if err != nil {
		panic(err)
	}
	defer db.Close()

	rows, err := db.Query("select w.team from rk3.workers w join (select * from rk3.times  where time > '9:00' and  type = 1 and w_date + 10 > now() ) as t on t.worker_id = w.id group by w.team")

	if err != nil {
		panic(err)
	}

	for rows.Next() {
		var team string
		rows.Scan(&team)
		fmt.Println(team)
	}
}

func workers_out(date string) {
	connStr := "user=nastya password=namtaehyun99 dbname=rk3 sslmode=disable"
	db, err := sql.Open("postgres", connStr)
	if err != nil {
		panic(err)
	}
	defer db.Close()

	rows, err := db.Query(" with max_out as (select max(cnt) from (select worker_id, count(*) as cnt from rk3.times where time between '9:00' and '18:00' and w_date = '$1' group by worker_id) as m) select fio from rk3.workers w where id in (select worker_id from (select worker_id, count(*) as cnt from rk3.times  where time between '9:00' and '18:00' and w_date = '$2' group by worker_id) as m where cnt =(select * from max_out))", date, date)

	if err != nil {
		panic(err)
	}

	for rows.Next() {

		var fio string
		rows.Scan(&fio)
		fmt.Println(fio)
	}
}

func main() {

	teams_with_late()
	workers_out("14-12-2018")

	/*
	   result, err := db.Exec("insert into dbo.Label (LabelID, CraeteDate, Title, Country, Creator) values ($1, $2, $3, $4, $5)",
	       1, "11.12.2009", "YG ENTERTAIMENT", "SOUTH KOREA", "YANG HEYN SOK")
	   if err != nil{
	       panic(err)
	   }*/

	//fmt.Println(reflect.TypeOf(db))
	// fmt.Println(faker.Name().Name())
}
