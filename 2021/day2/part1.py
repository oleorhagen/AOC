from aocutils import *

# table = {
#     "forward": math.sub,
#     "down": math.add,
#     "up": math.sub,
# }

# Two axis of freedom
# Let's store it in a two tuple

# So forward maps to the x-axis
# and (up,down) -> the z-axis

def p(inp):
    direction, size = inp.strip().split(" ")
    size = int(size)
    if direction == "forward":
        # Add in aim*size = z
        return (size, 0)
    elif direction == "up":
        return (0, -size)
    elif direction == "down":
        return (0, size)
    else:
        raise("Error, noooo")

d = data("part1.test", parser=p)

# Sum the vectors
assert math.prod(np.add.reduce(d)) == 150

d = data("part1.data", parser=p)

print(math.prod(np.add.reduce(d)))

# Part 2

# Now we need more of a collector on the parsed input pairs I would think

# Collect the input stream into a 3-tuple:
# (x,z,aim)

v = (0, 0, 0)

# This is really some kind of fold-left, how to do this in python (?)
def collect(input):
    global v
    # print(v)
    direction, size = input.strip().split(" ")
    size = int(size)
    if direction == "forward":
        # Add in aim*size = z
        aim = v[2]
        v = tuple(np.add(v, (size, aim*size, 0)))
        return tuple(np.add(v, (size, aim*size, 0)))
    elif direction == "up":
        v = tuple(np.add(v, (0, 0, -size)))
        return tuple(np.add(v, (0, 0, -size)))
    elif direction == "down":
        v = tuple(np.add(v, (0, 0, size)))
        return tuple(np.add(v, (0, 0, size)))
    else:
        raise("Error, noooo")

d = data("part1.test", parser=collect)

assert math.prod(v[:2]) == 900
# print(v)

# v = (0, 0, 0)

# d = data("part1.data", parser=collect)

# # Res = 1599311480
# print(math.prod(v[:2]))

#
#
# Fold f z xs
#
#
from functools import reduce

import functools
import operator

def foldl(func, acc, xs):
  return functools.reduce(func, xs, acc)

md = {
    "forward": lambda aim, size: (size, aim*size, 0),
    "up": lambda: _, size: (0, 0, -size),
    "down": lambda: _, size: (0, 0, size),
}

def p(input):
    direction, size = input.strip().split(" ")
    size = int(size)
    return (direction, size)

d = data("part1.test", parser=p)

def f(accumulator, input):
    direction, size = input.strip().split(" ")
    size = int(size)
    if direction == "forward":
        aim = accumulator[2]
        return tuple(np.add(accumulator, (size, aim*size, 0)))
    elif direction == "up":
        return tuple(np.add(accumulator, (0, 0, -size)))
    elif direction == "down":
        return tuple(np.add(accumulator, (0, 0, size)))
    else:
        raise("Error, noooo")

d = data("part1.test", parser=str)
assert math.prod(foldl(f, (0,0,0), d)[:2]) == 900

d = data("part1.data", parser=str)
assert math.prod(foldl(f, (0,0,0), d)[:2]) == 1599311480



