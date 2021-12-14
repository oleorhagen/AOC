from aocutils import *

def parser(d):
    pass

def valid_line(line, rights, lefts):
    stack = []
    lookup = {
        ")": 3,
        "]": 57,
        "}": 1197,
        ">": 25137,
    }
    def map(c):
        if c == "(":
            return ")"
        if c == "[":
            return "]"
        if c == "{":
            return "}"
        if c == "<":
            return ">"
    for c in line:
        if c in lefts:
            stack.append(map(c))
        elif c in rights:
            if c != stack[-1]:
                print(f"expected {stack[-1]} found {c} instead")
                return lookup[c]
            stack.pop()
    return 0

def solve_p1(input):
    lefts = ["[", "(", "<", "{"]
    rights = ["]", ")", ">", "}"]
    score = 0
    for line in input:
        score += valid_line(line, rights, lefts)
    return score


def valid_line_p2(line, rights, lefts):
    stack = []
    lookup = {
        ")": 1,
        "]": 2,
        "}": 3,
        ">": 4,
    }
    correction = []
    def map(c):
        if c == "(":
            return ")"
        if c == "[":
            return "]"
        if c == "{":
            return "}"
        if c == "<":
            return ">"
    for c in line:
        if c in lefts:
            stack.append(map(c))
        elif c in rights:
            if c != stack[-1]:
                print(f"expected {stack[-1]} found {c} instead")
                correction.append(stack[-1])
            stack.pop()

    tot = 0
    stack.reverse()
    for e in stack:
        tot = lookup[e] + tot*5
        print(f"stack: {e} tot: {tot}")
    if len(correction) > 0:
        for a in correction:
            tot = 5*tot + lookup[a]
    return tot

def valid_line_bool(line, rights, lefts):
    stack = []
    def map(c):
        if c == "(":
            return ")"
        if c == "[":
            return "]"
        if c == "{":
            return "}"
        if c == "<":
            return ">"
    for c in line:
        if c in lefts:
            stack.append(map(c))
        elif c in rights:
            if c != stack[-1]:
                return False
            stack.pop()
    return True


def solve_p2(l):
    lefts = ["[", "(", "<", "{"]
    rights = ["]", ")", ">", "}"]
    score = []
    def valid_line(l):
        return valid_line_bool(l, rights, lefts)
    lines = filter(valid_line, l)
    for line in lines:
        score.append(valid_line_p2(line, rights, lefts))
    return score[int(len(score)/2)]

# d = data('part1.test')

# res = solve_p1(d)
# assert res == 26397, res

# d = data('part1.data')
# print(solve_p1(d))

# Part 2
d = data('part1.test')
res = solve_p2(d)
assert res == 288957, res

d = data('part1.data')
res = solve_p2(d)
print(res)
