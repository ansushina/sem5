package main;

import (
    "database/sql"
    "fmt"
    _ "github.com/lib/pq"
    faker "syreclabs.com/go/faker"
    //"reflect"
    "os"

    "math/rand"
    //"bufio"
    "time"
    //"strconv"
)

const labelcnt int = 300
const artistcnt int = 700
const composercnt int = 500
const songscnt int = 1000
const sacnt int = 1200
const sccnt int = 1200

type FileWriter struct {
	filename string
}

func (f *FileWriter) Write(strSlice []string) error {
    fmt.Println(strSlice)
	file, err := os.Create(f.filename)
	if err != nil {
		return fmt.Errorf("can't open file")
	}
	defer file.Close()

	//writer := bufio.NewWriter(file)
	for _, row := range strSlice {
		file.WriteString(row)
		file.WriteString("\n")
	}
	return nil
}


/*
    LabelID int not null PRIMARY KEY ,
    CraeteDate date,
    Title varchar(30),
    Country varchar(40),
    Creator varchar(50)
*/

func create_labels(count int) []string {
    var strSlice []string
    for i := 0; i < count; i++ {
        str := fmt.Sprintf("%d;%s;%s;%s", 
            i+1000,
            faker.Company().Name(), 
            faker.Address().Country(), 
            faker.Name().Name());
        strSlice = append(strSlice, str)
    }

    return strSlice
}

func create_artists(count int) []string {
    var strSlice []string
    
    for i := 0; i < count; i++ {
        age := faker.Number().Between(15,90)
        sexNum := faker.Number().Between(0,1)
        label := faker.Number().Between(1000, labelcnt+1000 -1)
        sex := "male"
        if (sexNum == "1"){
            sex = "female"
        }

        str := fmt.Sprintf("%d;%s;%s;%s;%s;%s;%s", 
            i+1000,
            age,
            faker.Address().Country(),
            faker.Name().FirstName(),
            faker.Name().LastName(),
            sex, 
            label)
        strSlice = append(strSlice, str)
    }

    return strSlice
}

func create_mv(count int) []string {
    var strSlice []string
    for i := 0; i < count; i++ {
        str := fmt.Sprintf("%d;%s;%s", 
            i+1000,
            faker.Lorem().Word(),
            faker.Name().Name());
        strSlice = append(strSlice, str)
    }

    return strSlice
}

func create_songs(count int) []string {
    
    var strSlice []string
    for i := 0; i < count; i++ {
        str := fmt.Sprintf("%d;%s;%d", 
            i+1000,
            faker.Lorem().Word(),
            i+1000);
        strSlice = append(strSlice, str)
    }

    return strSlice
}

func create_sa(songscnt int,artistcnt int) []string {
    var strSlice []string
    for i := 0; i < sacnt; i++ {
        a := faker.Number().Between(1000, artistcnt+1000-1)
        s := faker.Number().Between(1000, songscnt+1000-1)
        str := fmt.Sprintf("%d;%s;%s", 
            i+1000,
            s,
            a);
        strSlice = append(strSlice, str)
    }

    return strSlice
}

func create_sc(songscnt int, composercnt int) []string {
    var strSlice []string
    for i := 0; i < sccnt; i++ {
        c := faker.Number().Between(1000, composercnt+1000-1)
        s := faker.Number().Between(1000, songscnt+1000-1)
        str := fmt.Sprintf("%d;%s;%s", 
            i+1000,
            s,
            c);
        strSlice = append(strSlice, str)
    }

    return strSlice
}

func main() {

    rand.Seed(time.Now().UnixNano())
    faker.Name().Name()

    //label := "LabelID, CraeteDate, Title, Country, Creator"

    connStr := "user=nastya password=namtaehyun99 dbname=MusicLabelsDB sslmode=disable"
    db, err := sql.Open("postgres", connStr)
    if err != nil {
        panic(err)
    } 
    defer db.Close()


    labels := create_labels(labelcnt)
    writer := FileWriter{"/tmp/labels.csv"}

    writer.Write(labels)

    artists := create_artists(artistcnt)
    writer = FileWriter{"/tmp/artist.csv"}
    writer.Write(artists)

    composers := create_artists(composercnt)
    writer = FileWriter{"/tmp/composers.csv"}
    writer.Write(composers)

    mv := create_mv(songscnt)
    writer = FileWriter{"/tmp/musicvideos.csv"}
    writer.Write(mv)

    songs := create_songs(songscnt)
    writer = FileWriter{"/tmp/songs.csv"} 
    writer.Write(songs)

    sa := create_sa(songscnt,artistcnt)
    writer = FileWriter{"/tmp/sa.csv"}
    writer.Write(sa)

    sc := create_sc(songscnt,composercnt)
    writer = FileWriter{"/tmp/sc.csv"}
    writer.Write(sc)

    //fmt.Println(artists)

   
    /* 
    result, err := db.Exec("insert into dbo.Label (LabelID, CraeteDate, Title, Country, Creator) values ($1, $2, $3, $4, $5)", 
        1, "11.12.2009", "YG ENTERTAIMENT", "SOUTH KOREA", "YANG HEYN SOK")
    if err != nil{
        panic(err)
    }*/

    //fmt.Println(reflect.TypeOf(db))
   // fmt.Println(faker.Name().Name())
}