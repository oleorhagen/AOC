
import os

tree = "#"


with open("input") as f:
    rows = f.read().split("\n")
    matrix = [[char for char in row] for row in rows if len(row) > 0]

def solve(right=3,down=1):
    trees = 0
    pos = complex(0,0)
    while pos.imag < len(matrix):
        # print("Yay")
        # print(f"Pos: {pos.real},{pos.real}")
        if matrix[int(pos.imag)][int(pos.real)] == tree:
            trees = trees + 1
        # print(f"right: {right}, down: {down}")
        # import pdb
        # pdb.set_trace()
        pos = pos + complex(right, down)
        pos = complex(pos.real % len(matrix[0]), pos.imag)
        # print(f"New pos: {pos.real},{pos.imag}")
        # print(trees)
    return trees


res = solve()

res = solve(right=1, down=1) * solve(right=3,down=1) * solve(right=5,down=1) * solve(right=7,down=1) * solve(right=1,down=2)
# print(len(matrix))
# print(len(matrix[1]))
# pos = (0,0)
# print(pos[0])
# print(pos[1])
# print(matrix[pos[0]][pos[1]])
# print("The solution is:")
print(res)
# print(trees)

