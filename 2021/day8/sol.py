from aocutils import *
from collections import Counter



def solvep1(d):
    counter = 0
    for line in d:
        for code in line:
            if len(code) in [2,3,4,7]:
                counter += 1
    return counter

def parser(l):
    o = l.split("|")[1]
    return [a for a in o.split(" ") if a != '']


d = data('part1.test', parser=parser, sep='\n')
assert solvep1(d) == 26, "count: {}".format(solvep1(d))

d = data('part1.data', parser=parser, sep='\n')
print(solvep1(d))

# Part 2

def deduce(l):
    # Do the gimmes
    for o in l:
        if len(o) == 2:
            one = o
        if len(o) == 4:
            four = o
        if len(o) == 3:
            seven = o
        if len(o) == 7:
            eight = o
    # Do the deductions
    for o in l:
        if len(o) == 5:
            if one.issubset(o):
                three = o
        if len(o) == 6:
            if four.issubset(o):
                nine = o
    for o in l:
        if len(o) == 6:
            if o != nine and one.issubset(o):
                zero = o
                continue
        if len(o) == 6 and o != nine:
            six = o
        if len(o) == 5:
            if o.issubset(nine) and o != three:
                five = o
                continue
        if len(o) == 5 and o != three:
            two = o

    return [zero, one, two, three, four, five, six, seven, eight, nine]


def parser(l):
    a = l.split("|")
    out = []
    for o in a:
        out.append([set(a) for a in o.split(" ") if a != ''])
    return out

def solve_p2(d):
    tot = 0
    for input_line in d:
        nrs = deduce(input_line[0])
        res = ""
        for disp in input_line[1]:
            for i, nr in enumerate(nrs):
                if nr == disp:
                    res += str(i)
                    break
        tot += int(res)
    return tot

d = data('part2.test', parser=parser, sep='\n')

res = deduce(d[0][0])

assert res[0] == set('cagedb')
assert res[1] == set('ab')
assert res[2] == set('gcdfa'), res[2]
assert res[3] == set('fbcad')
assert res[4] == set('eafb')
assert res[5] == set('cdfbe'), res[5]
assert res[6] == set('cdfgeb')
assert res[7] == set('dab')
assert res[8] == set('abcdefg')


d = data('part1.test', parser=parser, sep='\n')

assert solve_p2(d) == 61229

d = data('part1.data', parser=parser, sep='\n')

print(solve_p2(d))
