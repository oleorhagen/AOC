import sys

sys.path.append("../../aocutils")

from aocd.models import Puzzle

# Handy utility parser
import parse as p

from aocutils import *


def parser(d):
    return d.split("\n")


def solve_p1(d):
    def compare(a, b):
        if type(a) == int and type(b) == int:
            return b - a
        if type(a) == list and type(b) == list:
            for l, r in zip(a, b):
                if res := compare(l, r):
                    return res
            return len(b) - len(a)
        if type(a) == int and type(b) == list:
            return compare([a], b)
        if type(b) == int and type(a) == list:
            return compare(a, [b])

        assert False

    correct_order = []
    for i, (left, right) in enumerate(d):
        if res := compare(left, right) >= 1:
            correct_order.append(i + 1)
    return sum(correct_order)


def solve_p2(d):
    pass


td = data(Input("part1.test"), parser=parser, sep="\n\n")

tdd = [(eval(left), eval(right)) for left, right in td]

assert solve_p1(tdd) == 13

puzzle = Puzzle(year=2022, day=13)
d = data(puzzle.input_data, parser=parser, sep="\n\n")

dd = [(eval(left), eval(right)) for left, right in d]


puzzle.answer_a = solve_p1(dd)


# assert solve_p2(td) == 0

# puzzle.answer_b = solve_p2(d)
