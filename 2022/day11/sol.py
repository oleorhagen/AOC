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


def solve_p1(monkeys):
    # Do the rounds
    for round in range(20):
        for monkey_index in range(len(monkeys)):
            # Inspect the item
            new_items = []
            for item in monkeys[monkey_index]["items"]:
                monkeys[monkey_index]["inspection_count"] += 1
                new_worry_level = monkeys[monkey_index]["operation"](item) // 3
                if new_worry_level % monkeys[monkey_index]["test"] == 0:
                    monkeys[monkeys[monkey_index]["to_monkey_true"]]["items"].append(
                        new_worry_level
                    )
                else:
                    monkeys[monkeys[monkey_index]["to_monkey_false"]]["items"].append(
                        new_worry_level
                    )
            monkeys[monkey_index]["items"] = []

    inspection_counts = sorted([m["inspection_count"] for m in monkeys], reverse=True)
    return inspection_counts[0] * inspection_counts[1]


def print_monkeys(monkeys):
    # for i, m in enumerate(monkeys):
    #     print("Monkey: ", i)
    #     print(m)
    for i, m in enumerate(monkeys):
        print(f"Monkey: {i} inspected items: {m['inspection_count']}")
    print()


def solve_p2(monkeys):
    # Do the rounds
    for round in range(5):
        print_monkeys(monkeys)
        for monkey_index in range(len(monkeys)):
            # Inspect the item
            new_items = []
            for item in monkeys[monkey_index]["items"]:
                monkeys[monkey_index]["inspection_count"] += 1
                new_worry_level = monkeys[monkey_index]["operation"](item)
                if new_worry_level % monkeys[monkey_index]["test"] == 0:
                    monkeys[monkeys[monkey_index]["to_monkey_true"]]["items"].append(
                        new_worry_level
                        % monkeys[monkeys[monkey_index]["to_monkey_true"]]["test"]
                    )
                else:
                    monkeys[monkeys[monkey_index]["to_monkey_false"]]["items"].append(
                        new_worry_level
                        % monkeys[monkeys[monkey_index]["to_monkey_false"]]["test"]
                    )
            monkeys[monkey_index]["items"] = []

    # inspection_counts = sorted([m["inspection_count"] for m in monkeys], reverse=True)
    # return inspection_counts[0] * inspection_counts[1]


td = data(Input("part1.test"), parser=parser, sep="\n\n")

assert solve_p1(td) == 10605

puzzle = Puzzle(year=2022, day=11)
d = data(puzzle.input_data, parser=parser, sep="\n\n")

puzzle.answer_a = solve_p1(d)

td = data(Input("part1.test"), parser=parser, sep="\n\n")

solve_p2(td)


# assert solve_p2(td) == 0

# puzzle.answer_b = solve_p2(d)
