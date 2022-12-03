import sys

sys.path.append("../../aocutils")

from aocd.models import Puzzle

# Handy utility parser
import parse as p

puzzle = Puzzle(year=2022, day=3)

from aocutils import *

rucksacks = data(Input("part1.test"), sep="\n")

def solve(rucksacks):
    s = 0
    for rucksack in rucksacks:
        letters = list(rucksack)
        h = int(len(letters) / 2)
        common = first(set(letters[:h]) & set(letters[h:]))
        if common.islower():
            s += ord(common) - 96  # a = 1
        else:
            s += ord(common) - 65 + 27  # A = 27
    return s


rucksacks = data(puzzle.input_data)

puzzle.answer_a = solve(rucksacks)

# Part II

s = 0
while len(rucksacks) > 0:
    common = first(set(rucksacks.pop()) & set(rucksacks.pop()) & set(rucksacks.pop()))
    # import pdb; pdb.set_trace()
    if common.islower():
        s += ord(common) - 96  # a = 1
    else:
        s += ord(common) - 65 + 27  # A = 27

puzzle.answer_b = s


# puzzle.answer_a = 0
