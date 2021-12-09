# from .. import aocutils as aoc
import aocutils as aoc

# Add each number to all the entries listed in a dict

# Actions:
#
# 1 parser per line
#
# 2 parse the line

def increasing(a, b):
    if b > a:
        return 1
    return 0

def data(fname, parser=str, sep='\n') -> list:
    "Split the day's input file into sections separated by `sep`, and apply `parser` to each."
    sections = open(fname).read().rstrip().split(sep)
    return [parser(section) for section in sections]

def sol(dat):
    l = list(map(sum, map(list, zip(dat, dat[1:], dat[2:]))))
    return sum(map(increasing, l, l[1:]))

dat = data('part1.test', parser=int)
assert sol(dat) == 5

dat = data('part1.data', parser=int)
print("Sol:")

print(sol(dat))
