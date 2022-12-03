import sys

from ../../aocutils import *

rucksacks = data(Input("part1.test"), sep="\n")

lookup = lambda c: c - 96 if c >= 97 else c - 38

sum1 = 0
for rucksack in rucksacks:
    half = int(len(rucksack) / 2)
    common = (set(rucksack[:half]) & set(rucksack[half:])).pop()
    sum1 += lookup(ord(common))

print("Part I: ", sum1)

# Part II

sum2 = 0
for i in range(0, len(rucksacks), 3):
    s1, s2, s3 = rucksacks[i:i+3]
    common = (set(s1) & set(s2) & set(s3)).pop()
    sum2 += lookup(ord(common))

print("Part II: ", sum2)
