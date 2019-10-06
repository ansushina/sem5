package main;

import (
    "database/sql"
    "fmt"
    _ "github.com/lib/pq"
    faker "syreclabs.com/go/faker"
    "reflect"
    "os"

    "math/rand"
    //"bufio"
    "time"
    "strconv"
)

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


func create_labels(count int) []string {
    var strSlice []string
    for i := 0; i < count; i++ {
        str := fmt.Sprintf("%s, %s, %s", 
            
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
        ageNum,_ := strconv.Atoi(age)
        sexNum := faker.Number().Between(0,1)
        sex := "male"
        if (sexNum == "1"){
            sex = "female"
        }

        str := fmt.Sprintf("%s, %s, %s, %s, %s, %s", 
            age,
            faker.Address().Country(),
            faker.Date().Birthday(0, ageNum), 
            faker.Name().FirstName(),
            faker.Name().LastName(),
            sex)
        strSlice = append(strSlice, str)
    }

    return strSlice
}

func create_composers(count int) []string {
    var strSlice []string
    
    for i := 0; i < count; i++ {
        age := faker.Number().Between(15,90)
        ageNum,_ := strconv.Atoi(age)
        sexNum := faker.Number().Between(0,1)
        sex := "male"
        if (sexNum == "1"){
            sex = "female"
        }

        str := fmt.Sprintf("%s, %s, %s, %s, %s, %s", 
            age,
            faker.Address().Country(),
            faker.Date().Birthday(0, ageNum), 
            faker.Name().FirstName(),
            faker.Name().LastName(),
            sex)
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


    labels := create_labels(5)
    writer := FileWriter{"labels.txt"}

    writer.Write(labels)

    artists := create_artists(5)
    fmt.Println(artists)
   
    /* 
    result, err := db.Exec("insert into dbo.Label (LabelID, CraeteDate, Title, Country, Creator) values ($1, $2, $3, $4, $5)", 
        1, "11.12.2009", "YG ENTERTAIMENT", "SOUTH KOREA", "YANG HEYN SOK")
    if err != nil{
        panic(err)
    }*/

    fmt.Println(reflect.TypeOf(db))
    fmt.Println(faker.Name().Name())
}