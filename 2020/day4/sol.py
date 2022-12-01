import os
import sys
import re

# 1. parse the input

# 2. validate the parsed input grammar

# valid(passport) = (0 or 1)
# f : passport -> {0,1}


#1. extract each batch from the input stream
#
# Sounds like a regex to me
# [^\n]+\n([^\n])*

with open("test.fail" if len(sys.argv) == 1 else "input") as f:
    data = f.read()

# print(data)

def next_input(input):
    p = re.compile("[^\n]+(\n|\Z)([^\n]+(\n|\Z))*")
    return p.finditer(input)


def validate(passport):
    tokens = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"] # cid can be ignored
    for token in tokens:
        if token not in passport:
            return 0, f"token {token}: not in batch"
    return 1, "" if "cid" in passport.keys() else "missing cid (OK)"

def validate_height(s):
    try:
        if "cm" in s:
            m =  re.match("([0-9]{3})cm", s)
            if not m:
                return False
            return 150 <= int(m.group(1)) <= 193
        elif "in" in s:
            m = re.match("([0-9]{2})in", s)
            if not m:
                return False
            return 59 <= int(m.group(1)) <= 76
        else:
            return False
    except IndexError:
        print(f"Failed regex (?) {s}")
        import pdb
        pdb.set_trace()
        return False

def validatev2(passport):
    try:
        return all([1920 <= int(passport["byr"]) <= 2002,
                   2010 <= int(passport["iyr"]) <= 2020,
                   2020 <= int(passport["eyr"]) <= 2030,
                   validate_height(passport["hgt"]),
                   re.match("^#([a-f]|\d){6}", passport["hcl"]) is not None,
                   passport["ecl"] in ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"],
                   re.match("^\d{9}$", passport["pid"]) is not None,]
                   )
    except KeyError:
        return 0

def normalize(input):
    return " ".join(input.split("\n"))

tot = 0
batches = 0
for batch in next_input(data):
    res = batch.group()
    res = normalize(res)
    passport = {y.split(":")[0]:y.split(":")[1] for y in re.split(" |\n", res) if len(y) }
    # print(res)
    # print(passport)
    # res, reason = validate(passport)
    res = validatev2(passport)
    if res == 1:
        # print(f"Valid! {reason}")
        # print("")
        print(batches)
        print("Valid")
    else:
        print(batches)
        print("Invalid")
        # print(reason)
        # print("----------")
        # print("")
    print("")
    # if batches == 123:
    #     print(passport)
    #     sys.exit(0)
    batches += 1
    tot += res


print("Total")
print(tot)

# print("Batches")
# print(batches)
