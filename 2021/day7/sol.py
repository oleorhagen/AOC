from aocutils import *
import numpy as np

# Optimization problem

# min = min(o) Sum |xi - o| for all o

# min(D(v) -> o*)
# o* Is the optimal line to align on.
#
# So in general, the minimal amount of fuel spent aligning the crabs.
#

def solve(d):
    omin = min(d)
    omaz = max(d)

    ss = []
    m = 100000
    for o in range(omin, omaz+1):
        # print("o: {}".format(o))
        s = 0
        for e in d:
            # sum[ei - o] for all e
            s += abs(e - o)
            # if o == 2:
            #     print("s: {}-{} {}".format(e, o,s))
        ss.append(s)
        if s < m:
            m = o
    # print("Position: {}".format(m))
    # print("costs: {}".format(ss))
    # print("input: {}".format(d))
    return min(ss)


d = data('part1.test', parser=int, sep=',')
assert solve(d) == 37


d = data('part1.data', parser=int, sep=',')
print(solve(d))

# Part 2


def solvep2(d):
    omin = min(d)
    omaz = max(d)

    def cumsum(a):
        return int((a*(a+1))/2)

    ss = []
    m = 100000
    for o in range(omin, omaz+1):
        # print("o: {}".format(o))
        s = 0
        for e in d:
            # sum[ei - o] for all e
            s += cumsum(abs(e - o))
            # if o == 5:
            #     print("s: {}-{} {}".format(e, o,s))
        ss.append(s)
        if s < m:
            m = o
    # print("Position: {}".format(m))
    # print("costs: {}".format(ss))
    # print("input: {}".format(d))
    return min(ss)



d = data('part1.test', parser=int, sep=',')
assert solvep2(d) == 168

d = data('part1.data', parser=int, sep=',')
print(solvep2(d))
