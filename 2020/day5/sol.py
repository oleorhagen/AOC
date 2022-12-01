import sys

with open("test" if len(sys.argv) == 1 else "input") as f:
    data = f.read()


def map_R_to_B(I):
    return {
        "F": "0",
        "B": "1",
    }.get(I)

def map_C_to_B(C):
    return {
        "L": "0",
        "R": "1",
    }.get(C)

def split(input):
    row = input[:7]
    row_str = "".join([map_R_to_B(char) for char in row])
    # col = input[7:]
    row_int = int(row_str, 2)
    # print(row)
    # print(row_str)
    # print(row_int)
    col = input[7:]
    col_str = "".join([map_C_to_B(char) for char in col])
    col_int = int(col_str, 2)
    # print(col_int)
    # print("Seat ID:")
    return row_int * 8  + col_int


# for line in data.split("\n"):
#     print(max([split(line]))split(line)

# print(max([split(line) for line in data.split("\n")]))


# Part 2


def split(input):
    row = input[:7]
    row_str = "".join([map_R_to_B(char) for char in row])
    row_int = int(row_str, 2)
    col = input[7:]
    col_str = "".join([map_C_to_B(char) for char in col])
    col_int = int(col_str, 2)
    return row_int * 8  + col_int

# First find the missing ID's

IDs = [split(line) for line in data.split("\n")]

print(IDs)
print(sorted(set(IDs)))

IDs = sorted(set(IDs))

# Generate a set of all the ID's in the range min(set),max(set)
full = [x for x in range(IDs[0], IDs[-1])]
print("Set difference:")
print(set(full) - set(IDs))
# print((list(set(IDs)).sort(reverse=True)))


