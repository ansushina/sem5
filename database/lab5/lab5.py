from jsonschema import exceptions, validate
import json
import os

json_schema = input("Input path to json-schema: ")
json_doc = input("Input path to json: ")
f_schema = open(json_schema, "r")
f_doc = open(json_doc, "r")
flag = True
if f_schema and f_doc:
    schema = json.load(f_schema)
    f_schema.close()
    for line in f_doc:
        line = json.loads(line)
        try:
            validate(instance = line, schema = schema)
        except exceptions.ValidationError:
            print("Validation error!")
            print("In line: ")
            print(line)
            flag = False
            break
    f_doc.close()
if (flag):
    print("Validation end good")
