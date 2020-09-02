import csv
import cs50
import sys
import string

db = cs50.SQL("sqlite:///students.db")

if len(sys.argv) == 2:
    entry = sys.argv[1]

name = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ?", entry)

for row in name:
    if row["middle"] == " ":
        print(row["first"],row["last"] + ",", "born", row["birth"])
    else:
        print(row["first"], row["middle"], row["last"] + ",", "born", row["birth"])
