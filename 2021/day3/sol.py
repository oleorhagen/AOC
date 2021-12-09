from aocutils import *
import os


import functools
import operator

def foldl(func, acc, xs):
  return functools.reduce(func, xs, acc)

def p(input):
    return list(input.rstrip())

# Idea, create the strings vertically, and then simply add them to the Counter
# collection


d = data("part1.test", parser=p)

# Array of strings strings collected vertically
def collect(accumulator, input):
    for i in range(len(accumulator)):
        accumulator[i] = accumulator[i] + input[i]
    return accumulator



import collections as co

gamma = 0
epsilon = 0

for s in zip(range(len(d[0])-1,-1, -1), foldl(collect, ['' for i in range(len(d[0]))], d)):
    c = co.Counter(s[1])
    gamma += 2**s[0]*int(c.most_common()[0][0])
    epsilon += 2**s[0]*int(c.most_common()[1][0])

assert gamma*epsilon == 198, gamma*epsilon

d = data('part1.data', p)

stringified = foldl(collect, ['' for i in range(len(d[0]))], d)

assert len(stringified) == len(d[0])

gamma=0
epsilon=0

for s in zip(range(len(d[0])-1,-1, -1), stringified):
    c = co.Counter(s[1])
    gamma += 2**s[0]*int(c.most_common()[0][0])
    epsilon += 2**s[0]*int(c.most_common()[1][0])

print(gamma*epsilon)


#
# Part 2
#

# Find the oxygen generator rating

d = data('part1.test')

# Every index is then a filter on the set of numbers

vertical_strings = lambda d: foldl(collect, ['' for i in range(len(d[0]))], d)

def most_common_number(string):
    c =  co.Counter(list(string))
    if c.get('1', 0) >= c.get('0', 0):
        return '1'
    return '0'

def least_common_number(string):
    c =  co.Counter(list(string))
    if c.get('1', 0) >= c.get('0', 0):
        return '0'
    return '1'

def get_oxygen(candidates):
    for index in range(len(candidates[0])):
        nr = most_common_number(vertical_strings(candidates)[index])
        if os.getenv("DEBUG"):
            print(f"index: {index}")
            print(f"nr: {nr}")
            print(f"candidates: {candidates}")
            import pdb; pdb.set_trace()
        candidates = list(filter(lambda s: s[index] == nr, candidates))

        if len(candidates) == 1:
            return candidates[0]


def get_scrubber(candidates):
    for index in range(len(candidates[0])):
        nr = least_common_number(vertical_strings(candidates)[index])
        candidates = list(filter(lambda s: s[index] == nr, candidates))
        if os.getenv("DEBUG"):
            import pdb; pdb.set_trace()
        if len(candidates) == 1:
            return candidates[0]

assert int(get_oxygen(d), 2) * int(get_scrubber(d), 2) == 230


d = data('part1.data')

print (int(get_oxygen(d), 2) * int(get_scrubber(d), 2))
