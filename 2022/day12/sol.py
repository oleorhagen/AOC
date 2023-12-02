import sys


sys.path.append("../../aocutils")

from aocutils import neighbours4

from aocutils import *

from aocd.models import Puzzle

# Handy utility parser
import parse as p

from aocutils import *

import string

a = string.ascii_lowercase + "S" + "E"


class Matrix:
    def __init__(self, matrix, max_x, max_y):
        self.max_x = max_x
        self.max_y = max_y
        self.matrix = matrix

    def __getitem__(self, point):
        assert type(point) == tuple
        assert len(point) == 2
        x, y = point
        if 0 <= x <= self.max_x or 0 <= y <= self.max_y:
            return self.matrix[point[1]][point[0]]
        return 1e4

    def __setitem__(self, key, value):
        assert type(key) == tuple
        assert len(key) == 2
        self.matrix[key[1]][key[0]] = value

    def neighbours4(self, point):
        "Return the 4 neighbours of point in the Matrix"
        ns = []
        for p in neighbours4(point):
            if 0 <= p[0] < self.max_x and 0 <= p[1] < self.max_y:
                ns.append(p)
        return ns


def dmin(matrix, cost_matrix, start, end):
    "Run Dijkstra's Algorithm on the graph"

    # Initialize the cost matrix
    cost_matrix[start] = 0

    frontier = [(0, start)]
    visited = []

    def filter_moves(cur_height, moves):
        "Simple legal moves filter"
        points = []
        for move in moves:
            if matrix[move] - cur_height > 1:
                continue
            points.append(move)
        return points

    while len(frontier) != 0:
        cost, node = heappop(frontier)
        if node == end:
            return cost_matrix[end]
        # For all neigbhours, update the cost
        for point in filter_moves(matrix[node], matrix.neighbours4(node)):
            if point not in [(x, y) for _, (x, y) in frontier] and point not in visited:
                heappush(frontier, (cost + 1, point))
                cost_matrix[point] = cost + 1
            elif point in [(x, y) for _, (x, y) in frontier]:
                pass
        visited.append(node)

    return 1e4
    # raise Exception("No solution found!")


def solve_p1(matrix, cost_matrix, start, end):

    return dmin(matrix, cost_matrix, start, end)


def solve_p2(d):
    pass


def parse_input(inp):
    matrix = onesmat((200, 200)) * 1000
    cost_matrix = onesmat((200, 200)) * 1000
    start = None
    end = None
    for y, line in enumerate(inp.split("\n")):
        for x, c in enumerate(line):
            if c == "S":
                start = (x, y)
                c = "a"
            if c == "E":
                end = (x, y)
                c = "z"
            matrix[y][x] = a.index(c)
    return matrix, cost_matrix, start, end


matrix, cost_matrix, start, end = parse_input(Input("part1.test"))

matrix = Matrix(matrix, max_x=len(matrix[0]), max_y=len(matrix))
cost_matrix = Matrix(cost_matrix, max_x=len(cost_matrix[0]), max_y=len(cost_matrix))

sol = solve_p1(matrix, cost_matrix, start, end)
assert sol == 31, sol


puzzle = Puzzle(year=2022, day=12)
d = data(puzzle.input_data, sep="\n")

matrix, cost_matrix, start, end = parse_input(puzzle.input_data)

matrix = Matrix(matrix, max_x=len(matrix[0]), max_y=len(matrix))
cost_matrix = Matrix(cost_matrix, max_x=len(cost_matrix[0]), max_y=len(cost_matrix))

# puzzle.answer_a = solve_p1(matrix, cost_matrix, start, end)

# Do the same for all a's

# matrix, cost_matrix, start, end = parse_input(Input("part1.test"))

# matrix = Matrix(matrix, max_x=len(matrix[0]), max_y=len(matrix))
# cost_matrix = Matrix(cost_matrix, max_x=len(cost_matrix[0]), max_y=len(cost_matrix))
_as = []
breakpoint()
for y, col in enumerate(matrix.matrix):
    for x, row in enumerate(col):
        if row == 1000:
            continue
        print(row)
        if row == 0:
            _as.append((x, y))


print(_as)

puzzle.answer_b = min([solve_p1(matrix, cost_matrix, s, end) for s in _as])

# assert solve_p2(td) == min([solve_p1(matrix, cost_matrix, s, end) for s in _as])

# puzzle.answer_b = solve_p2(d)
