import sys

sys.path.append("../../aocutils")

from aocd.models import Puzzle
from aocutils import *

puzzle = Puzzle(year=2022, day=1)

elves = data(puzzle.input_data, parser=ints, sep="\n\n")

print("Part I: ", max(map(sum, elves)))
print("Part II: ", sum(sorted(map(sum, elves))[-3:]))
