import sys
sys.path.append("../../aocutils")

from aocd.models import Puzzle

# Handy utility parser
import parse as p

from aocutils import *

def parser(d):
    pass

def solve_p1(d):
    pass

def solve_p2(d):
    pass

td = data(Input('part1.test'))

paths = []
for path in td:
    paths.append([(x,y) for x,y in zip(ints(path)[::2], ints(path)[1::2])])

print (paths)

# Create the map
# through drawing the lines


assert solve_p1(paths) == 0

puzzle = Puzzle(year=2022, day=14)
d = data(puzzle.input_data, parser=parser, sep="\n")

# puzzle.answer_a = solve_p1(d)



# assert solve_p2(td) == 0

# puzzle.answer_b = solve_p2(d)
