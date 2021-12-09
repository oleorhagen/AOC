# from .. import aocutils as aoc
import aocutils as aoc

def increasing(a, b):
    if b > a:
        return 1
    return 0

def parse(text):
    return [int(s.strip()) for s in text.split()]

inp = parse(aoc.Input("part1.data").read())
print(sum(map(increasing, inp, inp[1:])))
