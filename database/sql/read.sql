BULK INSERT MusicLabelsDB.dbo.Label
FROM '//home/nastya/c_prog/sem5/database/labels.txt'
WITH ( DATAFILETYPE = 'char', FIELDTERMINATOR = ',',  ROWTERMINATOR = '0x0a')

Go