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
    return sum([values[i-1]*i for i in range(20, 221, 40)])

def solve_p2(d):
    pass

td = data(Input('part1.test'))

assert solve_p1(td) == 13140, solve_p1(td)

puzzle = Puzzle(year=2022, day=10)
d = data(puzzle.input_data)

puzzle.answer_a = solve_p1(d)



# assert solve_p2(td) == 0

# puzzle.answer_b = solve_p2(d)
