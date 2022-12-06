import sys
sys.path.append("../../aocutils")

from aocd.models import Puzzle

# Handy utility parser
import parse as p

from aocutils import *

def solve_p1(d):
    stream = [c for c in d]
    for i in range(len(stream) - 4):
        if len(set(stream[i:i+4])) == 4:
            return i+4
    raise Exception("No unique sequence found")


def solve_p2(d):
    stream = [c for c in d]
    for i in range(len(stream) - 14):
        if len(set(stream[i:i+14])) == 14:
            return i+14
    raise Exception("No unique sequence found")


tdd = data(Input('part1.test'))[0]
assert solve_p1(td) == 7

puzzle = Puzzle(year=2022, day=6)

d = data(puzzle.input_data)[0]
puzzle.answer_a = solve_p1(d)

assert solve_p2(td) == 19

puzzle.answer_b = solve_p2(d)

