from aocutils import *


def p(input):
    l = [point.strip() for point in input.split("->")]
    a = [tuple(map(int, point.split(","))) for point in l]
    return a

def nmat(size=1000):
    return np.zeros(size*size, dtype=int).reshape(size,size)

# Idea create a matrix for every vector, with ones in each line, and just add
# them all together.

# Line should be a function.
#
# p_(k+1) = p_(k) + v/|v|
#

def normalize(v):
    v = np.array(v)
    vs = []
    for n in v/np.sqrt(np.sum(v**2)):
        if n < 0:
            vs.append(math.floor(n))
            continue
        vs.append(math.ceil(n))
    return vs
    # return v / np.sqrt(np.sum(v**2))



# FIXME: Alternatively, I can create all the points between x1 and x2
# Much easier!
# TODO - handle diagonal lines
def vpoints(p1, p2):
    p2 = np.array(p2, dtype=int)
    p1 = np.array(p1, dtype=int)
    v = p2 - p1
    vn = normalize(v)
    p = p1
    yield ((int(p[0])), int(p[1]))
    while True:
        p = p + vn
        if (p == p2).all():
            yield tuple(p2)
            break
        yield ((int(p[0])), int(p[1]))
    # xs = [x for x in range(p1[0], p2[0])]
    # ys = [y for y in range(p1[1], p2[1])]
    # import pdb; pdb.set_trace()
    # return list(zip(xs,ys))


def linetomatrix(a,b):
    mat = nmat()
    for p in vpoints(a, b):
        mat[p] += 1
    return mat

def straight(line):
    a = np.array(line[0])
    b = np.array(line[1])
    return 0 in a - b

def solve(lines):
    matrices = []
    for line in lines:
        matrices.append(linetomatrix(line[0], line[1]))
    # Now that we have populated all the matrices, sum them
    tot = nmat()
    for mat in matrices:
        tot += mat
    # NOTE: Untested still
    def maptoone(x):
        if x >=2:
            return 1
        return 0
    return sum(map(maptoone, tot.flatten()))

a = (0,9)
b = (5,9)
pts = vpoints(a,b)
assert (next(pts) == (0,9))
assert (next(pts) == (1,9))
assert (next(pts) == (2,9))
assert (next(pts) == (3,9))
assert (next(pts) == (4,9))
assert (next(pts) == (5,9))

a = (2,2)
b = (2,1)
pts = vpoints(a,b)
assert(next(pts) == (2,2))
assert(next(pts) == (2,1))


def solve_p1():
    lines = data('part1.test', parser=p)
    straight_lines = filter(lambda l: straight(l), lines)
    res = solve(straight_lines)
    assert res == 5, f"res: {res}"
    lines = data('part1.data', parser=p)
    straight_lines = filter(lambda l: straight(l), lines)
    print(solve(straight_lines))

# solve_p1()

# Part 2, also consider <b>diagonal lines</b>


# Handle horizontal lines
a = (9,7)
b = (7,9)
pts = vpoints(a,b)
assert(next(pts) == (9,7))
assert(next(pts) == (8,8))
assert(next(pts) == (7,9))

def solve_p2():
    lines = data('part1.test', parser=p)
    res = solve(lines)
    assert res == 12
    lines = data('part1.data', parser=p)
    res = solve(lines)
    print(res)

solve_p2()


