import sys

with open("test.txt" if len(sys.argv) == 1 else "input.txt") as f:
    data = f.read()

total_unique_answers = 0
for group in data.split("\n\n"):
    unique_answers = set()
    for person in group.split("\n"):
        for answer in person:
            unique_answers.add(answer)
    total_unique_answers += len(unique_answers)

# print(total_unique_answers)

# 4 all groups -> 4 all persons -> 4 all answers

# part II

tot = 0

for group in data.split("\n\n"):
    allsets = []
    for person in group.split("\n"):
        answers = set()
        for answer in person:
            answers.add(answer)
        if len(answers) != 0:
            allsets.append(answers)
    tot += len(set.intersection(*allsets))

print(tot)


# Refac

# Have an iterator for groups
