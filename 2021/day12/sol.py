import sys

sys.path.append("../aocutils")

from aocutils import *


def parser(d):
    return d.split("-")


Paths = List[str]

def dfs(path, neighbors) -> Iterable[Path]:
    """All paths that start with `path` and lead to 'end' using `neighbors`.
    Small caves can only be visited once."""
    if path[-1] == 'end':
        yield [path]
    else:
        for cave in neighbors[path[-1]]:
            if cave.isupper() or cave not in path:
                yield from dfs(path + [cave], neighbors)

def dfs2(path, neighbours) -> Iterable[Path]:
    if path[-1] == 'end':
        yield [path]
    else:
        for cave in neighbours[path[-1]]:
            if cave.isupper() or cave not in path:
                yield from dfs2(path + [cave], neighbours)
            elif cave.islower() and cave != "start":
                yield from dfs(path + [cave], neighbours)


d = data('part1.test', parser=parser)

neighbours = multimap(d, symmetric=True)

assert quantify(dfs2(["start"], neighbours)) == 36

from aocd.models import Puzzle
puzzle = Puzzle(year=2021, day=12)

d = data(puzzle.input_data_fname, parser=parser)

neighbours = multimap(d, symmetric=True)

puzzle.answer_b = quantify(dfs2(["start"], neighbours))
