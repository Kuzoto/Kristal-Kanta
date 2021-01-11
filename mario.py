import cs50


def main():  # execute the print stairs function
    mario()
    

def get_positive_int():  # get integer
    while True:  # continue looping forever until break
        n = cs50.get_int("Positive Integer: ")  # request positive integer from user
        if n > 0 and n < 9:  # check if user input is positive and less than 9   
            return n  # return user input and break loop

        
def mario():  # print stairs
    x = get_positive_int()  # run get_positive_int and store it as the max number of blocks
    s = x  # store the number of steps/rows needed for the stairs
    for i in range(x):  # loop until final step
        for i in range(x):  # print first step
            if i < s-1:  # print a blank if i is less than the current step being printed
                print(" ", end="")  # print blank
            else:  # print block if i is greater than current step being printed
                print("#", end="")  # print block
        print("  ", end="")  # print spaces in between the staircases
        for i in range(x):  # print reflected step
            if i == x-s+1:  # exit loop if i is equal to max blocks minus current step plus 1
                break  # exit loop
            else:  # print block when if statement is false
                print("#", end="")  # print block
        print("")  # print white space/new-line
        s -= 1


main()  # execute the main function to execute the print stairs function