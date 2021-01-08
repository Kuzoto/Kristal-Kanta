import cs50
import csv
import sys
import time
import pandas as pd

#active sequence counter
AGATC = 0
TTTTTTCT = 0
AATG = 0
TCTAG = 0
GATA = 0
TATC = 0
GAAA = 0
TCTG = 0

#most repeats counter
rAGATC = 0
rTTTTTTCT = 0
rAATG = 0
rTCTAG = 0
rGATA = 0
rTATC = 0
rGAAA = 0
rTCTG = 0

#checks if there are 3 arguments
if len(sys.argv) == 3:
    csvf = open(sys.argv[1], "r")
    txtf = open(sys.argv[2], "r")
    txt = txtf.read()
    #loads dna sequence and checks for repeats
    for i in range(len(txt)):
        if txt[i:i+4] == "AATG":
            for x in range(i, len(txt), 4):
                if txt[x:x+4] == "AATG":
                    AATG += 1
                else:
                    if AATG > rAATG:
                        rAATG = AATG
                    AATG = 0
                    break
    #loads dna sequence and checks for repeats
    for i in range(len(txt)):
        if txt[i:i+5] == "AGATC":
            for x in range(i, len(txt), 5):
                if txt[x:x+5] == "AGATC":
                    AGATC += 1
                else:
                    if AGATC > rAGATC:
                        rAGATC = AGATC
                    AGATC = 0
                    break
    #loads dna sequence and checks for repeats
    for i in range(len(txt)):
        if txt[i:i+4] == "GATA":
            for x in range(i, len(txt), 4):
                if txt[x:x+4] == "GATA":
                    GATA += 1
                else:
                    if GATA > rGATA:
                        rGATA = GATA
                    GATA = 0
                    break
    #goes to first position of GAAA and starts counting
    pos = txt.find('GAAA')
    while pos >= 0:
        for x in range(pos, len(txt), 4):
            if txt[x:x+4] == "GAAA":
                GAAA += 1
            else:
                if GAAA > rGAAA:
                    rGAAA = GAAA
                GAAA = 0
                break
            pos += 4
        pos = txt.find('GAAA', pos)
    #goes to first position of TATC and starts
    pos = txt.find('TATC')
    while pos >= 0:
        for x in range(pos, len(txt), 4):
            if txt[x:x+4] == "TATC":
                TATC += 1
            else:
                if TATC > rTATC:
                    rTATC = TATC
                TATC = 0
                break
            pos += 4
        pos = txt.find('TATC', pos)
    #goes to first position of TCTAG and starts
    pos = txt.find('TCTAG')
    while pos >= 0:
        for x in range(pos, len(txt), 5):
            if txt[x:x+5] == "TCTAG":
                TCTAG += 1
            else:
                if TCTAG > rTCTAG:
                    rTCTAG = TCTAG
                TCTAG = 0
                break
            pos += 5
        pos = txt.find('TCTAG', pos)
    #goes to first position of TTTTTTCT and starts
    pos = txt.find('TTTTTTCT')
    while pos >= 0:
        for x in range(pos, len(txt), 8):
            if txt[x:x+8] == "TTTTTTCT":
                TTTTTTCT += 1
            else:
                if TTTTTTCT > rTTTTTTCT:
                    rTTTTTTCT = TTTTTTCT
                TTTTTTCT = 0
                break
            pos += 8
        pos = txt.find('TTTTTTCT', pos)
    #goes to first position of TCTG and starts
    pos = txt.find('TCTG')
    while pos >= 0:
        for x in range(pos, len(txt), 4):
            if txt[x:x+4] == "TCTG":
                TCTG += 1
            else:
                if TCTG > rTCTG:
                    rTCTG = TCTG
                TCTG = 0
                break
            pos += 4
        pos = txt.find('TCTG', pos)
    #open dna counts for small.csv and check for a name
    if sys.argv[1] == "dna/databases/small.csv":
        with open("dna/databases/small.csv", 'r') as csvfile:
            data = csv.reader(csvfile, delimiter=',')
            for column in data:
                if column[0] != 'name':
                    if int(column[1]) == rAGATC and int(column[2]) == rAATG and int(column[3]) == rTATC:
                        print(column[0])
                        i = 1
            if i != 1:
                print("No match")
    else:
        #if large.csv is arg then open csv file and check whos dna it is
        with open("dna/databases/large.csv", 'r') as csvfile:
            data = csv.reader(csvfile, delimiter=',')
            for column in data:
                if column[0] != 'name':
                    if int(column[1]) == rAGATC and int(column[2]) == rTTTTTTCT and int(column[3]) == rAATG and int(column[4]) == rTCTAG and int(column[5]) == rGATA and int(column[6]) == rTATC and int(column[7]) == rGAAA and int(column[8]) == rTCTG:
                        print(column[0])
                        i = 1
            #if no matches print no matches
            if i != 1:
                print("No match")
else:
    #error code for missing command arguments
    print("Error too Few Command-Line Arguments\nError Code: Elf")
