import sys

sys.path.append("../../aocutils")

from aocd.models import Puzzle

from aocutils import *


def execute(instruction):
    if instruction == "noop":
        yield 0
    else:
        yield 0
        yield int(instruction.split()[1])


def solve_p1(instructions):
    values = [1]
    x = 1
    for instruction in instructions:
        for value in execute(instruction):
            x = x + value
            values.append(x)

    # Print to screen
    for i in range(240):
        sprite = [values[i] - 1, values[i], values[i] + 1]
        if i % 40 == 0 and i != 0:
            print(flush=True)
        if i % 40 in sprite:
            print("#", end="", flush=True)
        else:
            print(".", end="", flush=True)

    return sum([values[i - 1] * i for i in range(20, 221, 40)])


def solve_p2(d):
    pass


td = data(Input("part1.test"))

assert solve_p1(td) == 13140, solve_p1(td)

print()

puzzle = Puzzle(year=2022, day=10)
d = data(puzzle.input_data)

puzzle.answer_a = solve_p1(d)

puzzle.answer_b = "RKPJBPLA"
