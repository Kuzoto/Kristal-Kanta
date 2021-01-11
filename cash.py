import cs50

while True:
    owed = cs50.get_float("Change owed: ")
    if owed >= 0:
        break

coins = round(owed * 100)

q = 25
d = 10
n = 5
p = 1

cCount = 0


while coins != 0:
    if coins >= q:
        cCount += 1
        coins -= q
    elif coins >= d and coins < q:
        cCount += 1
        coins -= d
    elif coins >= n and coins < d:
        cCount += 1
        coins -= n
    elif coins >= p:
        cCount += 1
        coins -= p
    
    
print(cCount)