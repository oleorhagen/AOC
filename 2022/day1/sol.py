
import sys
sys.path.append("../../aocutils")

from aocd.models import Puzzle

puzzle = Puzzle(year=2022, day=1)

# Handy utility parser
import parse as p

from aocutils import *

def solve_p1(d):
    puzzle.answer_a =  max(map(sum, d))

def solve_p2(d):
    answer = sum(sorted(map(sum,d))[-3:])
    puzzle.answer_b = answer


# Test case
d = data(Input('part1.test'), parser=ints, sep="\n\n")
# Sum the sections, and then max the array
assert max(map(sum, d)) == 24000

# Parse the actual problem data
d = data(puzzle.input_data, parser=ints, sep="\n\n")

solve_p1(d)

solve_p2(d)



# puzzle.answer_a = 0
