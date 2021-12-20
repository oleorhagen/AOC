import sys
sys.path.append("../aocutils")

from aocd.models import Puzzle
import parse as p
from aocutils import *

instr = open('part1.test').read()

dots  = [(x,y) for x,y in p.findall('{:d},{:d}', instr)]
folds = [(axis, pos) for axis, pos in p.findall('{:l}={:d}', instr)]

import matplotlib.pyplot as plt

def fold(dots, instruction):
    axis, line = instruction
    if axis == 'x':
        return {(line - abs(line - x), y) for (x, y) in dots}
    else:
        return {(x, line - abs(line - y)) for (x, y) in dots}

def origami(dots, instructions) -> None:
    """Follow all the instructions and plot the resulting dots."""
    for instruction in instructions:
        dots = fold(dots, instruction)
        import pdb; pdb.set_trace()
    plt.scatter(*transpose(dots), marker='s')
    plt.axis('equal'); plt.gca().invert_yaxis()
    plt.show()


origami(dots, folds)


