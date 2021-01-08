import cs50

name = cs50.get_string("What is your name?\n")
if str(name):
    print("hello, " + name)
else:
    if str(name):
        print("hello, " + name)
    else:
        name = cs50.get_string("Please enter a string\n")
        if str(name):
            print("hello, " + name)
        else:
            print("Error: string not entered")