import sys

sys.path.append("../../aocutils")

from aocd.models import Puzzle

from aocutils import *

puzzle = Puzzle(year=2022, day=6)

f = lambda stream, window: first(
    [
        i + window
        for i in range(len(stream) - window)
        if len(set(stream[i : i + window])) == window
    ]
)

puzzle.answer_a = f(letters(puzzle.input_data), window=4)

puzzle.answer_b = f(letters(puzzle.input_data), window=14)
