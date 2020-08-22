
def main():
    mario()

def get_positive_int():
    while True:
        n = int(input("Positive Integer: "))
        if n > 0:
            break
    return n
        
def mario():
    x = get_positive_int()
    s = x
    for i in range(x):
        for i in range(x):
            if i < s-1:
                print(" ", end="")
            else:
                print("#", end="")
        print(" ", end="")
        for i in range(x):
            if i >= x-s+1:
                print(" ", end="")
            else:
                print("#", end="")
        print("")
        s -= 1




main()