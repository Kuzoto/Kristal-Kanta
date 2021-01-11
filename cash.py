import cs50

while True:
    owed = cs50.get_float("Change owed: ")  # query user for a float of change owed
    if owed >= 0:  # check if float is a valid value/not a string or less than 0
        break

coins = round(owed * 100)  # change owed to a whole number

# declare variables for each coin and their values
q = 25
d = 10
n = 5
p = 1

cCount = 0  # declare variable for total coins needed


while coins != 0:  # continue looping while change is still owed
    if coins >= q:  # check if coins is greater than 25
        cCount += 1  # add 1 to coins
        coins -= q  # subtract a quarter from coins
    elif coins >= d and coins < q:  # check if coins is greater than 9 and less than 25
        cCount += 1  # add 1 to coins
        coins -= d  # subtract a dime from coins
    elif coins >= n and coins < d:  # check if coins is greater than 4 and less than 10
        cCount += 1  # add 1 to coins
        coins -= n  # subtract a nickel from coins
    elif coins >= p:  # check if coins is greater than or equal to 1
        cCount += 1  # add 1 to coins
        coins -= p  # subtract a penny from coins
    
    
print(cCount)  # print the total number of coins needed