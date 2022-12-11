import sys

sys.path.append("../../aocutils")

from aocd.models import Puzzle

from aocutils import *


def parser(d):
    monkey = {}
    data = d.split("\n")
    monkey["items"] = list(ints(data[1]))
    monkey["operation"] = lambda old: eval(data[2].split("=")[1])
    monkey["test"] = ints(data[3])[0]
    monkey["to_monkey_true"] = ints(data[4])[0]
    monkey["to_monkey_false"] = ints(data[5])[0]
    monkey["inspection_count"] = 0
    return monkey


def solve(monkeys, rounds=20, level_normalizer=lambda x: x // 3):
    for round in range(rounds):
        for monkey in monkeys:
            # Inspect the item
            for item in monkey["items"]:
                monkey["inspection_count"] += 1
                new_worry_level = level_normalizer(monkey["operation"](item))
                if new_worry_level % monkey["test"] == 0:
                    monkeys[monkey["to_monkey_true"]]["items"].append(new_worry_level)
                else:
                    monkeys[monkey["to_monkey_false"]]["items"].append(new_worry_level)
            monkey["items"] = []

    inspection_counts = sorted([m["inspection_count"] for m in monkeys], reverse=True)
    return inspection_counts[0] * inspection_counts[1]


def solve_p1(monkeys):
    return solve(monkeys)


def solve_p2(monkeys):
    # Do the rounds
    cf = math.prod(m["test"] for m in monkeys)
    print("CF: ", cf)
    return solve(monkeys, rounds=10 * 1000, level_normalizer=lambda x: x % cf)


td = data(Input("part1.test"), parser=parser, sep="\n\n")

assert solve_p1(td) == 10605

puzzle = Puzzle(year=2022, day=11)
d = data(puzzle.input_data, parser=parser, sep="\n\n")

puzzle.answer_a = solve_p1(d)

td = data(Input("part1.test"), parser=parser, sep="\n\n")

assert solve_p2(td) == 2713310158

d = data(puzzle.input_data, parser=parser, sep="\n\n")

puzzle.answer_b = solve_p2(d)
