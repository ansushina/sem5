import psycopg2

con = psycopg2.connect(
  database="mynewdatabase_db", 
  user="nastya", 
  password="", 
)

print("Database opened successfully")
cur = con.cursor()  
cur.execute('''CREATE TABLE STUDENT  
     (ADMISSION INT PRIMARY KEY NOT NULL,
     NAME TEXT NOT NULL,
     AGE INT NOT NULL,
     COURSE CHAR(50),
     DEPARTMENT CHAR(50));''')

print("Table created successfully")
con.commit()  
con.close()
