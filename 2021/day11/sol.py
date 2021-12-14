from aocutils import *

# Need to keep a marker for flashed cells
# A flash need only generate a matrix wit hall the 8 neighbours surrounding set
# to one - then we add them together

def parser(d):
    return np.array(list(d), dtype=int)


def zeromat(size):
    return np.zeros(size, dtype=int)

def idmat(size):
    return np.ones(size, dtype=int)


def addition_matrix(point, size):
    m = np.zeros(size, dtype=int)
    for i in neighbours8(point):
        if i[0] < 0 or i[1] < 0:
            continue
        try:
            m[i] = 1
        except:
            pass
    return m

def flash(d, cell_flashed):
    flashes = 0
    for i in range(len(d)):
        for j in range(len(d[0])):
            if d[i][j] > 9 and cell_flashed[i][j] != 1:
                cell_flashed[i][j] = 1
                # Flash
                d += addition_matrix((i,j), d.shape)
                flashes += 1
    return flashes

def solve_p1(d, n_steps):
    flashes = 0
    for i in range(n_steps):
        print("before")
        print(d)
        # 1. Iterate
        d += idmat(d.shape)
        # 2. Flash
        cell_flashed = mat(d.shape)
        while True:
            f = flash(d, cell_flashed)
            if f == 0:
                break
            flashes += f
        # Reset the flashed cells
        d[d > 9] = 0
        print(f"after: {i+1}")
        print(d)
    return flashes



def flash_sync(d, cell_flashed):
    flashes = 0
    for i in range(len(d)):
        for j in range(len(d[0])):
            if d[i][j] > 9 and cell_flashed[i][j] != 1:
                cell_flashed[i][j] = 1
                # Flash
                d += addition_matrix((i,j), d.shape)
                flashes += 1
    return (cell_flashed == idmat(d.shape)).all(), flashes


def solve_p2(d, n_steps):
    for i in range(n_steps):
        # 1. Iterate
        d += idmat(d.shape)
        # 2. Flash
        cell_flashed = mat(d.shape)
        while True:
            sync, flashes = flash_sync(d, cell_flashed)
            if sync:
                return i
            if flashes == 0:
                break
        # Reset the flashed cells
        d[d > 9] = 0
    return flashes


d = np.array(data('part1.test', parser=parser))

res = solve_p1(d, 10)

assert res == 204, res


d = np.array(data('part1.data', parser=parser))

res = solve_p1(d, 100)

print(res)

# Part 2

d = np.array(data('part1.test', parser=parser))

res = solve_p2(d, 1000)

assert res+1 == 195, res

d = np.array(data('part1.data', parser=parser))

res = solve_p2(d, 1000)

print(res+1)
