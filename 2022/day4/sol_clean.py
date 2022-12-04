import sys

sys.path.append("../../aocutils")
from aocutils import *

# Handy utility parser
import parse as p
from aocd.models import Puzzle


def parse_line(line):
    a, b = line.split(",")
    a1, a2 = a.split("-")
    b1, b2 = b.split("-")
    return int(a1), int(a2), int(b1), int(b2)


def solve(data):
    hits = 0
    for line in data:
        a1, a2, b1, b2 = parse_line(line)
        # Case 1: first interval contained in the second
        if a1 >= b1 and a2 <= b2:
            hits = hits + 1
        # Case 2: second interval contained in the first
        elif b1 >= a1 and b2 <= a2:
            hits = hits + 1
    return hits


def solveII(data):
    hits = 0
    for line in data:
        a1, a2, b1, b2 = parse_line(line)
        # Case 1: first interval overlaps with the second
        if a1 >= b1 and a1 <= b2:
            hits = hits + 1
        # Case 2: second interval overlaps with the first
        elif b1 >= a1 and b1 <= a2:
            hits = hits + 1
    return hits


# Test base-case
testdata = data(Input("part1.test"))

puzzle = Puzzle(year=2022, day=4)
puzzle_data = data(puzzle.input_data)

# Part I
assert solve(testdata) == 2
puzzle.answer_a = solve(puzzle_data)


# Part II
assert solveII(testdata) == 4
puzzle.answer_b = solveII(puzzle_data)
