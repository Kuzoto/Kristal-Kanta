import cs50
import sys
import csv
import time


def sortText():  # scan text for the different key words and symbols
    lNum = 0  # variable storing the number of letters
    wNum = 1  # variable storing the number of words, starts with one due to it not counting the final word
    sNum = 0  # variable storing the number of sentences
    i = 0  # variable to keep track of where the program is is in the text
    user = cs50.get_string('Enter Text To Grade: ')  # retrieve text from the user to scan and grade
    n = len(user)  # store the length of the input to tell how many times the for loop needs to run
    spaces = 0  # a count of the number of spaces uptil the next word
    words = 0  # a count telling whether or not a space is the end of a word
    for i in range(n): 
        if user[i].isalnum() == True:  # checks if the current character is alpha numeric
            lNum += 1
            spaces = 0
            words = 0
        elif user[i] == '?' or user[i] == '!' or user[i] == '.' and user[i-1].isalnum():  # checks if the current character is a period, exclamation mark, or question mark and the previous character was alpha numeric
            sNum += 1 
            spaces = 0
            words = 0
        elif user[i] == '\0':  # checks if current space is null 
            spaces += 1
        elif user[i].isspace():  # checks if current spot is a space
            if words == 0:  # adds to word count if space is deamed as the end of a word if words variable is equal to 0
                wNum += 1
                words += 1
            spaces = 0
        else: 
            spaces = 0
            words = 0
    gradeText(lNum, wNum, sNum)
    

def gradeText(lNum, wNum, sNum):  
    index = 0.0588 * (100 * lNum / wNum) - 0.296 * (100 * sNum / wNum) - 15.8  # equation used to grade the text
    if index >= 1 and index < 16: 
        print("Grade:", round(index))  # prints the numerical grade
    elif index < 1:
        print("Before Grade 1")  # prints that the grade is less than 1
    elif index >= 16:
        print("Grade 16+")  # prints that the grade is over 16
    else:
        print("Index Error: Neanderthal\nGrading has returned", round(index),
        "due to an error.")  # prints an error when the grade is invalid
        response = cs50.get_string("Would you like to exit the program or retry?(exit/restart)")
        if response == "exit":
            return "exited"
        elif response == "restart":
            sortText()
        else:
            return "Invalid response. Stopping program" 


sortText()