def get_height(prompt):
    while True:
        try:
            height = int(input(prompt))
            if height <= 0:
                print("Invalid height")
            elif height >= 9:
                print("Maximum height is 8")
            else:
                return height
        except ValueError:
            print("Not an integer")


h = get_height("Height: ")

for i in range(1, h + 1):
    print(" " * (h - i) + "#" * i + "  " + "#" * i)
