# Python 3.x
#
# Thank you, Peter Norvig!
#
# TODO - add the foldl and foldr functions here!
import re
import numpy as np
import math
import urllib.request

from typing import *

from collections import Counter, defaultdict, namedtuple, deque
from functools import lru_cache
from itertools import permutations, combinations, chain, cycle, product, islice
from heapq import heappop, heappush


def Input(day):
    "Open this day's input file."
    filename = day
    return open(filename).read()


def data(inp, parser=str, sep="\n") -> list:
    "Split the day's input file into sections separated by `sep`, and apply `parser` to each."
    sections = inp.rstrip().split(sep)
    return [parser(section) for section in sections]


def transpose(matrix):
    return zip(*matrix)


def first(iterable):
    return next(iter(iterable))


def nth(iterable, n, default=None):
    "Returns the nth item of iterable, or a default value"
    return next(islice(iterable, n, None), default)


cat = "".join

Ø = frozenset()  # Empty set
inf = float("inf")
BIG = 10 ** 999
positive_infinity = BIG


def grep(pattern, lines):
    "Print lines that match pattern."
    for line in lines:
        if re.search(pattern, line):
            print(line)


def groupby(iterable, key=lambda it: it):
    "Return a dic whose keys are key(it) and whose values are all the elements of iterable with that key."
    dic = defaultdict(list)
    for it in iterable:
        dic[key(it)].append(it)
    return dic


def powerset(iterable):
    "Yield all subsets of items."
    items = list(iterable)
    for r in range(len(items) + 1):
        for c in combinations(items, r):
            yield c


# 2-D points implemented using (x, y) tuples
def X(point):
    return point[0]


def Y(point):
    return point[1]


def neighbours4(point):
    "The four neighbors (without diagonals)."
    x, y = point
    return ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1))


def neighbours8(point):
    "The eight neighbors (with diagonals)."
    x, y = point
    return (
        (x + 1, y),
        (x - 1, y),
        (x, y + 1),
        (x, y - 1),
        (x + 1, y + 1),
        (x - 1, y - 1),
        (x + 1, y - 1),
        (x - 1, y + 1),
    )


def cityblock_distance(p, q=(0, 0)):
    "City block distance between two points."
    return abs(X(p) - X(q)) + abs(Y(p) - Y(q))


def euclidean_distance(p, q=(0, 0)):
    "Euclidean (hypotenuse) distance between two points."
    return math.hypot(X(p) - X(q), Y(p) - Y(q))


def trace1(f):
    "Print a trace of the input and output of a function on one line."

    def traced_f(*args):
        result = f(*args)
        print("{}({}) = {}".format(f.__name__, ", ".join(map(str, args)), result))
        return result

    return traced_f


def astar_search(start, h_func, moves_func):
    "Find a shortest sequence of states from start to a goal state (a state s with h_func(s) == 0)."
    frontier = [
        (h_func(start), start)
    ]  # A priority queue, ordered by path length, f = g + h
    previous = {start: None}  # start state has no previous state; other states will
    path_cost = {start: 0}  # The cost of the best path to a state.
    while frontier:
        (f, s) = heappop(frontier)
        if h_func(s) == 0:
            return Path(previous, s)
        for s2 in moves_func(s):
            new_cost = path_cost[s] + 1
            if s2 not in path_cost or new_cost < path_cost[s2]:
                heappush(frontier, (new_cost + h_func(s2), s2))
                path_cost[s2] = new_cost
                previous[s2] = s
    return dict(fail=True, front=len(frontier), prev=len(previous))


def Path(previous, s):
    "Return a list of states that lead to state s, according to the previous dict."
    return [] if (s is None) else Path(previous, previous[s]) + [s]


def quantify(iterable, pred=bool) -> int:
    """Count the number of items in iterable for which pred is true."""
    return sum(1 for item in iterable if pred(item))

###########################
# Matrix initialization #
###########################


def zeromat(size):
    return np.zeros(size, dtype=int)

def onesmat(size):
    return np.ones(size, dtype=int)

def idmat(size):
    return np.identity(size, dtype=int)

def popmat(mat, coordinates, _with=1):
    "Populate the given matrix with the coordinates array"
    for coordinate in coordinates:
        mat[coordinate] = _with

class multimap(defaultdict):
    """A mapping of {key: [val1, val2, ...]}."""
    def __init__(self, pairs: Iterable[tuple], symmetric=False):
        """Given (key, val) pairs, return {key: [val, ...], ...}.
        If `symmetric` is True, treat (key, val) as (key, val) plus (val, key)."""
        self.default_factory = list
        for (key, val) in pairs:
            self[key].append(val)
            if symmetric:
                self[val].append(key)


###########
# Parsers #
###########

def lines(string):
    return string.split('\n')

def paragraph(string):
    return string.split("\n\n")

def ints(text: str) -> Tuple[int]:
    """A tuple of all the integers in text, ignoring non-number characters."""
    return mapt(int, re.findall('-?[0-9]+', text))

def digits(text: str) -> Tuple[int]:
    """A tuple of all the digits in text (as ints 0–9), ignoring non-digit characters."""
    return mapt(int, re.findall('[0-9]', text))

def words(text: str) -> List[str]:
    """A list of all the alphabetic words in text, ignoring non-letters."""
    return re.findall('[a-zA-Z]+', text)

def mapt(fn, *args) -> tuple:
    """map(fn, *args) and return the result as a tuple."""
    return tuple(map(fn, *args))

def tokens(matcher):
    def ma(text: str):
        return re.findall(matcher, text)
    return ma
