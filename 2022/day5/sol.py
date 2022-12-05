import sys

sys.path.append("../../aocutils")

from aocd.models import Puzzle

# Handy utility parser
import parse as p

from aocutils import *


def solvep1(data):
    stack, instructions = data[0], data[1]

    *stack, columns = stack.split("\n")

    stacks = [[] for i in range(len(columns.split()))]

    for row in reversed(stack):
        for i, char in enumerate(row):
            if char.isalpha():
                stacks[(i - 1) // 4].append(char)

    for instruction in instructions.split("\n"):
        nr_crates, _from, to = ints(instruction)
        for i in range(nr_crates):
            stacks[to - 1].append(stacks[_from - 1].pop())

    return "".join([stack[-1] for stack in stacks])


def solvep2(data):
    stack, instructions = data[0], data[1]


    *stack, columns = stack.split("\n")

    stacks = [[] for i in range(len(columns.split()))]

    for row in reversed(stack):
        for i, char in enumerate(row):
            if char.isalpha():
                stacks[(i - 1) // 4].append(char)

    for instruction in instructions.split("\n"):
        nr_crates, _from, to = ints(instruction)
        stacks[to - 1].extend(
            reversed([stacks[_from - 1].pop() for i in range(nr_crates)])
        )

    return "".join([stack[-1] for stack in stacks])


test_data = data(Input("part1.test"), sep="\n\n")
assert solvep1(test_data) == "CMZ"


puzzle = Puzzle(year=2022, day=5)

d = data(puzzle.input_data, sep="\n\n")
puzzle.answer_a = solvep1(d)

assert solvep2(test_data) == "MCD"

puzzle.answer_b = solvep2(d)
