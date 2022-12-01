import sys
sys.path.append("../aocutils")

from aocd.models import Puzzle
puzzle = Puzzle(year=2021, day=14)

# Handy utility parser
import parse as p

from aocutils import *

def parse_input(fname):
    d = data(fname, sep='\n\n')
    template = d[0]
    production_rules  = defaultdict(str, { x:y for x,y in p.findall('{:l} -> {:l}', d[1])})
    return template, production_rules

def tokens(template):
    "Return the two adjacent characters"
    for a, b in zip(list(template), list(template)[1:]):
        yield a, b

def produce(template, production_rules) -> str:
    ns = [template[0]]
    for r1, r2 in tokens(template):
        s = "".join([r1,r2])
        ns.append(production_rules[s])
        ns.append(r2)
    return "".join(ns)

def create_dict(template):
    d = defaultdict(int)
    for k,v in zip(list(template), list(template)[1:]):
        d[k+v] += 1
    return d


def pfast(template, production_rules, iterations) -> int:
    keys = create_dict(template)
    counter = Counter(template)
    for i in range(iterations):
        lookupkeys = keys.copy()
        newkeys = defaultdict(int)
        for key in keys.keys():
            # f(key) = (ci,ca), (ca,ci+1), ca
            ca = production_rules[key]
            c1, c2 = key
            n1, n2 = c1+ca, ca+c2
            if ca not in counter:
                counter[ca] = 1
            else:
                counter[ca] += lookupkeys[key]
            newkeys[n1] += lookupkeys[key]
            newkeys[n2] += lookupkeys[key]
        keys = newkeys
    return counter


def prod(template, production_rules, iterations) -> str:
    for i in range(iterations):
        print(i)
        template = produce(template, production_rules)
    return template

def answ(s) -> int:
    c = Counter(s)
    return c.most_common()[0][1] - c.most_common()[-1][1]


def test():
    template, production_rules  = parse_input('part1.test')
    assert prod(template, 1) == "NCNBCHB"
    assert prod(template, 2) == "NBCCNBBBCBHCB"
    assert prod(template, 3) == "NBBBCNCCNBBNBNBBCHBHHBCHB"
    assert prod(template, 4) == "NBBNBNBBCCNBCNCCNBBNBBNBBBNBBNBBCBHCBHHNHCBBCBHCB"
    assert answ(prod(template, 10)) == 1588

def part1():
    template, production_rules  = parse_input(puzzle.input_data_fname)
    a = answ(prod(template, production_rules, 10))
    print(a)
    puzzle.answer_a = a

def part2():
    template, production_rules  = parse_input(puzzle.input_data_fname)
    count = pfast(template, production_rules, 40)
    puzzle.answer_b = count.most_common()[0][1] - count.most_common()[-1][1]

# test()
# part1()
part2()

