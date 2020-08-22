import cs50

num = cs50.get_int("Enter A Valid Credit Card: ")
valid = False
i = 0

numS = num

while num != 0:
    num = (num - num % 10) / 10
    i += 1
    
num = numS
test = []

for x in range(i):
    test.append(num % 10)
    num = (num - num % 10) / 10
    print(test[x])
    
checkSum = 0

for x in range(i):
    if x % 2 != 0:
        checkSum = checkSum + (test[x] * 2)
    else:
        checkSum = checkSum + test[x]

print(checkSum % 10)
if checkSum % 10 == 0:
    valid = True

if test[i-1] == 5:
    print("MASTERCARD")
elif test[i-1] == 3:
    print("AMEX")
elif test[i-1] == 4:
    print("VISA")
else:
    print("INVALID")