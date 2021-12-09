from aocutils import *
import numpy as np

# This is really a recurrence relation of the form:
# fn = fn-7 + fn-9

# Solving this in Python yields, with all the initial conditions given by the input file.
# TODO - do this also

# Or we can model this as a dynamic system, with the Matrix

P = [
    [0, 1, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 1, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 1, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 1, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 1, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 1, 0, 0],
    [1, 0, 0, 0, 0, 0, 0, 1, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0],
]


# The inputs we can get, and then simply collect into the buckets for each day
# with a Counter, and then we simply iterate the given number of days


from collections import Counter

def solve(fname, days):
    global P

    d = data(fname, int, sep=',')

    i = Counter(d)

    # Initialize the vector
    v0 = []
    for v in range(9):
        v0.append(i[v])

    v0 = np.array(v0)
    P = np.array(P)

    # Do some base sanity checks

    # # Day 0
    # print(v0)

    # # 1 day
    # v0 = P.dot(v0)
    # assert sum(v0) == 5
    # print(v0)

    # # 2 days
    # v0 = P.dot(v0)
    # assert(sum(v0)) == 6
    # print(v0)

    # # 3 days
    # v0 = P.dot(v0)
    # assert sum(v0) == 7
    # print(v0)

    # # 4  days
    # v0 = P.dot(v0)
    # assert sum(v0) == 9
    # print(v0)

    # # 5 days
    # v0 = P.dot(v0)
    # assert sum(v0) == 10
    # print(v0)

    for i in range(1, days+1):
        v0 = P.dot(v0)

    return sum(v0)

res = solve('part1.test', 80)
assert res == 5934, "res: {}".format(res)

res = solve('part1.test', 256)
assert res == 26984457539, "res: {}".format(res)

print(solve('part1.data', 256))
