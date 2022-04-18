height = 0
while height < 1 or height > 300:
    height = int(input("Height: "))

for rows in range(1, height + 1):
    spaces = (height - rows)
    for spaces in range(spaces, 0, -1):
        print(" ", end='')

    for hashesLeft in range(1, rows + 1):
        print("#", end='')
    print(" ", end='')
    for hashesRight in range(1, rows + 1):
        print("#", end='')
    print("")
