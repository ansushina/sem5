r = plpy.execute("SELECT * FROM " + name1)
res = []
count = []
for i in range(len(r)):
    if (r[i]["age"] not in res):
        res.append(r[i]["age"])
        count.append(1)
    else:
	count[res.index(r[i]["age"]) += 1
for i in range(len(res)):
    plpy.execute("update "+name2+"set count = count"+count[i] + "where age=" + res[i])
