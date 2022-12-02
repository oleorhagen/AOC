import sys
sys.path.append("../../aocutils")

from aocd.models import Puzzle
puzzle = Puzzle(year=2022, day=2)

# Handy utility parser
import parse as p

points = {
    'X': 1,
    'Y': 2,
    'Z': 3,
}

lookup = {
    'A': {
        'X': 3,
        'Y': 6,
        'Z': 0,
    },
    'B': {
        'X': 0,
        'Y': 3,
        'Z': 6,
    },
    'C': {
        'X': 6,
        'Y': 0,
        'Z': 3,
    },
}

from aocutils import *

dt = data(Input('part1.test'), parser=words)

assert sum([lookup[x][y] + points[y] for x,y in dt]) == 15

d = data(puzzle.input_data, parser=words)

puzzle.answer_a = sum([lookup[x][y] + points[y] for x,y in d])

# Part II

# This is essentially a reverse-lookup in our table above:

translation = {
    'A': {
        'X': 'Z',
        'Y': 'X',
        'Z': 'Y',
    },
    'B': {
        'X': 'X',
        'Y': 'Y',
        'Z': 'Z',
    },
    'C': {
        'X': 'Y',
        'Y': 'Z',
        'Z': 'X',
    }
}


assert sum([lookup[x][translation[x][y]] + points[translation[x][y]] for x,y in dt]) == 12

puzzle.answer_b = assert sum([lookup[x][translation[x][y]] + points[translation[x][y]] for x,y in d])

