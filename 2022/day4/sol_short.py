import sys
sys.path.append("../../aocutils")
from aocutils import *
testdata = data(Input("part1.test"))

f = lambda a,b,c,d: 1 if (a>=c) and (b<=d) or (c>=a) and (d<=b) else 0
print("Part I: ", sum(f(*a) for a in [[int(j) for i in line.split(",") for j in i.split("-")] for line in testdata ]))

f = lambda a,b,c,d: 1 if (a>=c) and (a<=d) or (c>=a) and (c<=b) else 0
print("Part II: ", sum(f(*a) for a in [[int(j) for i in line.split(",") for j in i.split("-")] for line in testdata ]))
