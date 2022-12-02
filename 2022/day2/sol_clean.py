import sys

sys.path.append("../../aocutils")

from aocutils import *
from aocd.models import Puzzle

puzzle = Puzzle(year=2022, day=2)

rounds = data(puzzle.input_data, parser=words)

points = {
    "X": 1,
    "Y": 2,
    "Z": 3,
}

lookup = {
    "A": {"X": 3, "Y": 6, "Z": 0,},
    "B": {"X": 0, "Y": 3, "Z": 6,},
    "C": {"X": 6, "Y": 0, "Z": 3,},
}

print("Part I: ", sum([lookup[x][y] + points[y] for x, y in rounds]))

# Part II

# This is essentially a reverse-lookup in our table above:

translation = {
    "A": {"X": "Z", "Y": "X", "Z": "Y",},
    "B": {"X": "X", "Y": "Y", "Z": "Z",},
    "C": {"X": "Y", "Y": "Z", "Z": "X",},
}

print(
    "Part II: ",
    sum([lookup[x][translation[x][y]] + points[translation[x][y]] for x, y in rounds]),
)
