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


def touching(H, T):
    return distance(H, T) < 2


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
    # The head and tail must always be touching
    # 1.
    if touching(H, T):
        return (0, 0)
    # 2. not touching -> Then make sure we are once again touching
    if not touching(H, T):
        return direction(H, T)


def solve_p1(steps):
    # The head and tail must always be touching
    visited = set()
    H = (0, 0)
    T = (0, 0)
    for action in steps:
        _dir, iterations = action
        for move in range(int(iterations)):
            m = moves[action[0]]
            H = (H[0] + m[0], H[1] + m[1])
            r = rules(H, T)
            T = (T[0] + r[0], T[1] + r[1])
            visited.add(T)
    return len(visited)


def solve_p2(steps):
    # The head and tail must always be touching
    visited = set()
    H = (0, 0)
    Ts = [(0, 0) for i in range(9)]
    for action in steps:
        _dir, iterations = action
        for move in range(int(iterations)):
            m = moves[action[0]]
            H = (H[0] + m[0], H[1] + m[1])
            r = rules(H, Ts[0])
            Ts[0] = (X(Ts[0]) + r[0], Y(Ts[0]) + r[1])
            for i in range(len(Ts) - 1):
                r = rules(Ts[i], Ts[i + 1])
                Ts[i + 1] = (X(Ts[i + 1]) + r[0], Y(Ts[i + 1]) + r[1])
            visited.add(Ts[-1])
    return len(visited)


td = data(Input("part1.test"), parser=parser)

assert solve_p1(td) == 13

puzzle = Puzzle(year=2022, day=9)
d = data(puzzle.input_data, parser=parser, sep="\n")

puzzle.answer_a = solve_p1(d)

answ = solve_p2(td)
assert answ == 1, answ

puzzle.answer_b = solve_p2(d)
