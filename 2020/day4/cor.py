r = open('input').read().strip('\n')
import re
input = [[y.split(':') for y in re.split(' |\n',x)] for x in r.split('\n\n')]

# print(input)

#Part 1
def valid(passport):
    good = 0
    for entry in passport:
        if entry[0] in {'byr','iyr','eyr','hgt','hcl','ecl','pid'}:
            good = good + 1
    return good == 7

# print([valid(x) for x in input].count(True))

# Part 2
def valid(passport):
    good = 0
    for entry in passport:
        ok = False
        field = entry[0]
        data = entry[1]
        if field in {'byr','iyr','eyr'}:
            data = int(data)
            if field == 'byr' and 1920 <= data <= 2002:
                ok = True
            if field == 'iyr' and 2010 <= data <= 2020:
                ok = True
            if field == 'eyr' and 2020 <= data <= 2030:
                ok = True
        if field == 'hgt':
            unit = data[-2:]
            if unit in {'cm','in'}:
                data = int(data[:-2])
            if unit == 'cm' and 150 <= data <= 193:
                ok = True
            if unit == 'in' and 59 <= data <= 76:
                ok = True
        if field == 'hcl' and re.search('^#(\d|[a-f]){6}$',data) is not None:
            ok = True
        if field == 'ecl' and data in {'amb','blu','brn','gry','grn','hzl','oth'}:
            ok = True
        if field == 'pid' and re.search('^\d{9}$',data) is not None:
            ok = True
        if ok:
            good = good + 1
    return good == 7

# print([valid(x) for x in input].count(True))

for i,x in enumerate(input):
    if valid(x):
        print(i)
        print("Valid")
    else:
        print(i)
        print("Invalid")
    print("")
