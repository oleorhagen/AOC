from aocutils import *

# Create a stream which simply outputs the next number from the stream
def numbers(input):
    for line in input:
        l = line.rstrip()
        for n in l.split(" "):
            try:
                nr = int(n)
                yield nr
            except:
                continue


def populate_boards(boards, nrs):
    while nrs:
        mat = new_mat()
        try:
            pop_mat(mat, nrs)
        except StopIteration:
            break
        boards.append(Board(mat))


def new_mat():
    return np.ones(5 * 5).reshape(5, 5)


def pop_mat(mat, nrs):
    for row in range(5):
        for col in range(5):
            mat[row][col] = next(nrs)


class Board:
    def __init__(self, mat):
        self.mat = mat
        self.occ = new_mat()

    def drawn(self, nr):
        if float(nr) in self.mat:
            self.hit(float(nr))

    def hit(self, nr):
        for row in range(5):
            for col in range(5):
                if self.mat[row][col] == nr:
                    self.occ[row][col] = 0
                    return

    def win(self):
        for row in self.occ:
            if np.all(row == 0):
                return True
        for col in range(5):
            if np.all(self.occ[:, col] == 0):
                return True
        return False

    def board_score(self):
        return int(sum((self.mat * self.occ).flatten()))


# Part 1


def solve_p1(filename):

    # Play the game
    def play(drawn_numbers, boards):
        for drawn in drawn_numbers.rstrip().split(","):
            for b in boards:
                b.drawn(drawn)
                if b.win():
                    return b.board_score() * int(drawn)

    d = Input(filename)
    drawn_numbers = d.readline()
    nrs = numbers(d)
    boards = []
    populate_boards(boards, nrs)
    return play(drawn_numbers, boards)


assert solve_p1("part1.test") == 4512


# Part 2 - which board will win last!


def solve_p2(filename):
    def play(drawn_numbers, boards):
        last_winning_board = None
        for drawn in drawn_numbers.rstrip().split(","):
            to_remove = []
            for i in range(len(boards)):
                b = boards[i]
                b.drawn(drawn)
                if b.win():
                    to_remove.append(i)
                    last_winning_board = b
                    last_winning_score = int(drawn)
            if to_remove:
                boards = [boards[i] for i in range(len(boards)) if i not in to_remove]
        if not last_winning_board:
            print("Noooooooooo")
            return None
        return last_winning_board.board_score() * last_winning_score

    d = Input(filename)
    drawn_numbers = d.readline()
    nrs = numbers(d)
    boards = []
    populate_boards(boards, nrs)
    return play(drawn_numbers, boards)


assert solve_p2("part1.test") == 1924
print("Part 2 sol")
print(solve_p2("part1.data"))
print("Done")
