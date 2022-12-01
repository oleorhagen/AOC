import sys
sys.path.append("../aocutils")

from aocd.models import Puzzle
puzzle = Puzzle(year=2021, day=15)

# Handy utility parser
import parse as p

from aocutils import *

def parser(d):
    return np.array(list(map(int, list(d))))

def solve_p1(d):
    pass

def solve_p2(d):
    pass

# mat = np.array(data('part1.test', parser=parser))
import functools

def map_cost(n, length, cost):
    return (cost + n // 3 - 1/3) % length

@functools.lru_cache(maxsize=1000)
def dpme(x,y):
    global resmat, mat
    # import pdb; pdb.set_trace()
    if x >= 0 and y >= 0:
        if x == 0 and y == 0:
            # import pdb; pdb.set_trace()
            # yield resmat
            return 0
        else:
            try:
                # Cannot move diagonally, so left, right and top cells available
                cost = mat[x,y]
                # print(f"({x},{y})")
                c1 = dpme(x-1,y)
                c2 = dpme(x,y-1)
                # print(f"cost[{x-1},{y}] = {c1}")
                # print(f"cost[{x},{y-1}] = {c2}")
                # print(f"mat[{x},{y}] = {mat[x,y]} + min(cost[{x-1},{y}]):{c1}, cost[{x},{y-1}]):{c2} = {min(c1,c2)} = {mat[x,y] + min(c1,c2)}")
                resmat[x,y] = cost +  min(c1, c2)
                return resmat[x,y]
            except KeyError as e:
                # Out of the matrix indexing
                # print(f"out of matrix indexing: ({x},{y}): {e}")
                return positive_infinity
    else:
        return positive_infinity


# mat = mat[0:4,0:4]

# resmat = zeromat(mat.shape)

# res = dpme(mat.shape[0]-1, mat.shape[1]-1)


# assert res == 40
# import pdb; pdb.set_trace()


mat = np.array(data(puzzle.input_data_fname, parser=parser))

resmat = zeromat(mat.shape)

res = dpme(mat.shape[0]-1, mat.shape[1]-1)

import pdb; pdb.set_trace()
puzzle.answer_a = res


# Screams dynamic programming

#
# min(a(i)) = min((a(i-1,j), a(i,j-1), a(i-1,j-1)))
#


# puzzle.answer_a = 0
