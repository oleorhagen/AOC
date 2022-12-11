import sys

sys.path.append("../../aocutils")

from aocd.models import Puzzle

from aocutils import *

f = lambda stream, window: first([i + window for i in range(len(stream) - window) if len(set(stream[i : i + window])) == window])

test_letters = tokens("[a-zA-Z]")(open("part1.test").read())
assert f(test_letters, 4) == 7

puzzle = Puzzle(year=2022, day=6)

puzzle.answer_a = f(tokens("[a-z]")(puzzle.input_data), window=4)

puzzle.answer_b = f(tokens("[a-z]")(puzzle.input_data), window=14)

