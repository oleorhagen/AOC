import sys

sys.path.append("../../aocutils")

from aocd.models import Puzzle

# Handy utility parser
import parse as p

from aocutils import *


def parser(d):
    return [int(c) for c in d]


def is_visible(x, y, matrix):
    # check top
    height = matrix[y][x]
    print("is_visible()")
    print(f"x: {x}, y: {y}")
    print("coordinate: ", matrix[y][x])

    if len([yi for yi in range(y + 1, len(matrix)) if matrix[yi][x] >= height]) == 0:
        print("visible from the bottom")
        return True

    # check the bottom
    if len([yi for yi in range(0, y) if matrix[yi][x] >= height]) == 0:
        print("visible from the top")
        return True

    # check left
    if len([xi for xi in range(0, x) if matrix[y][xi] >= height]) == 0:
        print("visible from the left")
        return True

    # check right
    if len([xi for xi in range(x + 1, len(matrix)) if matrix[y][xi] >= height]) == 0:
        print("visible from the right")
        return True

    print("Not visible!")
    return False


def solve_p1(tree_matrix):
    "How many trees are visible?"
    # Rule: A tree is visible if all trees in one direction is lower than it
    #
    # Only check the trees in the interior

    # Solve for one tree
    edge_trees = len(tree_matrix) * 2 + len(tree_matrix[0]) * 2 - 4

    nr_visible = 0
    for i in range(1, len(tree_matrix[0]) - 1):
        for j in range(1, len(tree_matrix) - 1):
            print(i, j)
            print(tree_matrix[i][j])
            if is_visible(j, i, tree_matrix):
                nr_visible += 1
    return nr_visible + edge_trees


def solve_p2(d):
    pass


td = data(Input("part1.test"), parser=parser)
a = solve_p1(td)
assert a == 21, a

puzzle = Puzzle(year=2022, day=8)
d = data(puzzle.input_data, parser=parser)
puzzle.answer_a = solve_p1(d)


# assert solve_p2(td) == 0

# puzzle.answer_b = solve_p2(d)
