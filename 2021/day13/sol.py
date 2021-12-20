import sys
sys.path.append("../aocutils")

from aocd.models import Puzzle
import parse as p
from aocutils import *

puzzle = Puzzle(year=2021, day=13)

d = data('part1.test', sep='\n\n')
# d = data(puzzle.input_data_fname, sep='\n\n')

pts = mapt(ints, lines(d[0]))

instructions = [p.parse("fold along {direction}={where:d}",s) for s in lines(d[1])]

max_x = max(map(X, pts)) +1
max_y = max(map(Y, pts)) +1

mat = zeromat((max_x, max_y))

popmat(mat, pts)

for n, i in enumerate(instructions):
    if i["direction"] == "x":
        mat = np.transpose(mat)
    # Delete the column we're flipping on
    a = np.delete(mat, i["where"], 1)
    # Flip the matrices on top of eachother
    fold_at = a.shape[1]/2
    b = np.fliplr(a)
    # Add them together, element wise, and extract the sub-matrix
    c = (a + b)
    mat = c[0:int(c.shape[0]),0:int(c.shape[1]/2)]
    if i["direction"] == "x":
        mat = np.transpose(mat)


import matplotlib.pyplot as plt
import matplotlib.cm as cm

fig = plt.figure()
ax2 = fig.add_subplot(122)
# 'nearest' interpolation - faithful but blocky
mat[mat>1] = 1
# ax2.imshow(np.transpose(mat), interpolation='nearest', cmap=cm.Greys_r)
# plt.show()

mt = np.transpose(mat)

for line in mt:
    print(''.join(['o' if x else ' ' for x in line]))

# res = quantify(mat.flatten())
# assert res == 17, res
# puzzle.answer_a = quantify(mat.flatten())

import pdb; pdb.set_trace()

