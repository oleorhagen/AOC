import sys

sys.path.append("../../aocutils")

from aocd.models import Puzzle

# Handy utility parser
import parse as p

from aocutils import *


def parser(d):
    return d.split()


moves = {
    "R": (1, 0),
    "U": (0, 1),
    "L": (-1, 0),
    "D": (0, -1),
}


def distance(H, T):
    return math.sqrt(abs(X(H) - X(T)) ** 2 + abs(Y(H) - Y(T)) ** 2)


def scale(v):
    if v < 0:
        return -1
    if v > 0:
        return 1
    return 0


def direction(H, T):
    "Vector pointing from T -> H"
    return (scale(X(H) - X(T)), scale(Y(H) - Y(T)))


def rules(H, T):
    if distance(H, T) >= 2:
        return vect(direction(H, T))
    return vect((0, 0))


def solve(steps, nr_nots):
    visited = set()
    Ts = [vect((0, 0)) for i in range(nr_nots)]
    for action in steps:
        dir, iterations = action
        for move in range(int(iterations)):
            # Instigate
            Ts[0] = Ts[0] + vect(moves[dir])
            for i in range(len(Ts) - 1):
                Ts[i + 1] = Ts[i + 1] + rules(Ts[i], Ts[i + 1])
            visited.add(Ts[-1])
    return len(visited)


def solve_p1(steps):
    return solve(steps, 2)


def solve_p2(steps):
    # The head and tail must always be touching
    return solve(steps, 10)


puzzle = Puzzle(year=2022, day=9)
d = data(puzzle.input_data, parser=parser, sep="\n")

puzzle.answer_a = solve_p1(d)
puzzle.answer_b = solve_p2(d)
