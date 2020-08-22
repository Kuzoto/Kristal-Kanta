import cs50
import sys
import csv
import time



def sortText():
    lNum = 0
    wNum = 1
    sNum = 0
    i = 0
    user = cs50.get_string('Enter Text To Grade: ')
    n = len(user)
    spaces = 0
    words = 0
    for i in range(n):
        if user[i].isalnum() == True:
            lNum += 1
            spaces = 0
            words = 0
        elif user[i] == '?' or user[i] == '!' or user[i] == '.' and user[i-1].isalnum():
            sNum += 1
            spaces = 0
            words = 0
        elif user[i] == '\0':
            spaces += 1
        elif user[i].isspace():
            if words == 0:
                wNum += 1
                words += 1
            spaces = 0
        else:
            spaces = 0
            words = 0
    gradeText(lNum, wNum, sNum)

def gradeText(lNum, wNum, sNum):
    index = 0.0588 * (100 * lNum / wNum) - 0.296 * (100 * sNum / wNum) - 15.8
    if index >= 1 and index < 16:
        print("Grade:",round(index))
    elif index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print("Index Error: Neanderthal\nGrading has returned",round(index),"due to an error.")
        response = cs50.get_string("Would you like to exit the program or retry?(exit/restart)")
        if response == "exit":
            return "exited"
        elif response == "restart":
            sortText()
        else:
            return "Invalid response. Stopping program"


sortText()