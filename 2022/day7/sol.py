from collections import defaultdict
import sys

sys.path.append("../../aocutils")

from aocd.models import Puzzle

from aocutils import *

# 1. Generate a list of (dir - size)
#
# 2. Then traverse it and sum all subfolders into the super folders


def solvep1(movements):
    movements = [m for m in movements if m != ""]
    pwd = []
    visited = set()
    dirs = []

    for movement in movements:
        m = movement.split("\n")
        if len(m) == 0:
            continue
        _dir = m[0].strip()
        if _dir == "/":
            pwd = ["/"]
        elif _dir == "..":
            pwd.pop()
        else:
            pwd.append(_dir)
        if "/".join(pwd) in visited:
            continue
        else:
            visited.add("/".join(pwd))
        # Real command, sum directory
        dir_contents_size = 0
        a = filter(None, m[1:])
        for dir_contents in a:
            if dir_contents[0].isnumeric():
                size, _ = dir_contents.split()
                dir_contents_size += int(size)
        s = "/".join(pwd)
        dirs.append(
            {"dir": s, "size": dir_contents_size,}
        )

    # Then loop over the directories - and sum all the directories, including their sub-dirs
    def is_sub_dir_of(superdir={}, subdir={}):
        return subdir["dir"].startswith(superdir["dir"])

    dir_sums = {}
    for d in dirs:
        dir_sums[d["dir"]] = d["size"]
        for _d in dirs:
            if d == _d:
                continue
            if is_sub_dir_of(superdir=d, subdir=_d):
                dir_sums[d["dir"]] += _d["size"]

    # Then loop and sum the directory sums less than a 1e5
    print("Dir sum: ", dir_sums)
    return sum(i for i in dir_sums.values() if i <= 1e5)


a = Input("part1.test")
testdata = data(a, sep="$ cd")
assert solvep1(testdata) == 95437

puzzle = Puzzle(year=2022, day=7)
d = data(puzzle.input_data, sep="$ cd")
puzzle.answer_a = solvep1(d)


def solvep2(movements):
    movements = [m for m in movements if m != ""]
    pwd = []
    visited = set()
    dirs = []

    for movement in movements:
        m = movement.split("\n")
        if len(m) == 0:
            continue
        _dir = m[0].strip()
        if _dir == "/":
            pwd = ["/"]
        elif _dir == "..":
            pwd.pop()
        else:
            pwd.append(_dir)
        if "/".join(pwd) in visited:
            continue
        else:
            visited.add("/".join(pwd))
        # Real command, sum directory
        dir_contents_size = 0
        a = filter(None, m[1:])
        for dir_contents in a:
            if dir_contents[0].isnumeric():
                size, _ = dir_contents.split()
                dir_contents_size += int(size)
        s = "/".join(pwd)
        dirs.append(
            {"dir": s, "size": dir_contents_size,}
        )

    # Then loop over the directories - and sum all the directories, including their sub-dirs
    def is_sub_dir_of(superdir={}, subdir={}):
        return subdir["dir"].startswith(superdir["dir"])

    dir_sums = {}
    for d in dirs:
        dir_sums[d["dir"]] = d["size"]
        for _d in dirs:
            if d == _d:
                continue
            if is_sub_dir_of(superdir=d, subdir=_d):
                dir_sums[d["dir"]] += _d["size"]

    # Then loop and sum the directory sums less than a 1e5
    tot_size = 70000000
    # tot_size - space_taken + free' >= 30000000
    dir_size = 1e10 # positive infinity
    tot_space = int(dir_sums["/"])
    for k, v in dir_sums.items():
        if tot_size - tot_space + int(v) >= 30000000:
            dir_size = min(dir_size, int(v))

    return dir_size


answ = solvep2(testdata)
assert answ == 24933642, answ

puzzle.answer_b = solvep2(d)


# assert solve_p2(td) == 0

# puzzle.answer_b = solve_p2(d)
