import csv
import cs50
import sys
import string

db = cs50.SQL("sqlite:///students.db")

if len(sys.argv) == 2:
    
    with open(sys.argv[1], "r") as characters:
        reader = csv.DictReader(characters)
        for row in reader:
            parsed = row["name"].split()
            if len(parsed) == 2:
                db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                parsed[0], " " , parsed[1], row["house"], row["birth"])
            else:
                db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                parsed[0], parsed[1], parsed[2], row["house"], row["birth"]) 