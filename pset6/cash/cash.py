from cs50 import get_float


def main():
    changeowed = 0.00
    
    # ask user for input
    while changeowed <= 0.00:
        changeowed = get_float("Change owed: ")

    changeowed = round(changeowed * 100.00)
    
    # initialize needed variables
    qter = 25.00
    dme = 10.00
    nk = 5.00
    pn = 1.00
    coins = 0

    owechange = True

    # keep looping and adding the greatest possible coin until 0
    while changeowed > 0:
        if qter <= changeowed:
            changeowed -= qter
            coins += 1
        elif dme <= changeowed:
            changeowed -= dme
            coins += 1
        elif nk <= changeowed:
            changeowed -= nk
            coins += 1
        else:
            changeowed -= pn
            coins += 1
    
    # print out the number of coins
    owechange = False
    print(coins)


# call main
if __name__ == "__main__":
    main()