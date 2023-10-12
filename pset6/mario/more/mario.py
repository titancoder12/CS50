from cs50 import get_int


def main():
    # get user input
    x = get_int("Height: ")

    # repeatedly prompt user for imput if input greater than 8
    while x > 8 or x <= 0:
        x = get_int("Height: ")
   
    # print pyramid of height x
    for i in range(1, x+1, 1):
        # print spaces before left side of pyramind
        for j in range(x - i):
            print(" ", end="")

        # print left side of pyramind
        for j in range(i):
            print("#", end="")

        print("  ", end="")

        # print right side of pyramind
        for j in range(i):
            print("#", end="")

        print()


# run main
if __name__ == "__main__":
    main()