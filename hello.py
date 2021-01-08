import cs50

name = cs50.get_string("What is your name?\n")  # gets name from user
if str(name):  # checks if input was a string/not null
    print("hello, " + name)  # print hello, input
else:  # if null/not string reprompt user 
    name = cs50.get_string("Please enter a string\n")  # request string from user
    if str(name):  # checks if input was a string/not null
        print("hello, " + name)  # print hello, input
    else:  # if null/not string return error
        print("Error: string not entered")  # print error if they fail to enter a string twice