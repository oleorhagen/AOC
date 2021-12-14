
from aocutils import *


# Run a filter on all the surrounding elements
def solve_p1(d):
    print(d.shape)
    minimums = []
    for row in range(1,d.shape[0]-1):
        for col in range(1, d.shape[1]-1):
            # print((row,col))
            # print(mat)
            # print(mat[(row,col)])
            # print(mat[(5,10)])
            # If the element at (row,col) < all neighbours, then we have a minimum
            neigh = neighbours4((row,col))
            # print(neigh)
            neighbours = [mat[(a[0],a[1])] for a in neigh]
            # print(neighbours)
            if all([mat[row][col] < a for a in neighbours]):
                # minimums.append([row,col])
                # print("Found minimum!!!")
                minimums.append(mat[row][col])
    # print("Minimums")
    # print(minimums)
    # print(sum([a+1 for a in minimums]))
    return sum([a+1 for a in minimums])

def p(i):
    # Return a matrix of all the low points
    return [int(a) for a in i if a != '']

d = data('part1.test', parser=p)

def setup(d):
    d = np.array(d, dtype=int)

    mat = np.ones((d.shape[0] + 2, d.shape[1]+2), dtype=int)*9

    for i in range(d.shape[0]):
        for j in range(d.shape[1]):
            mat[i+1][j+1] = d[i][j]

    return mat

mat = setup(d)
assert solve_p1(mat) == 15

# Part 1

d = data('part1.data', parser=p)
mat = setup(d)

print(solve_p1(mat))


# Part 2

def solve_p2(m):
    pass
