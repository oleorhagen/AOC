// Copyright 2024 <Ole P. Orhagen>

#include "../utils.hpp"

#include <set>
#include <thread>

using namespace std::chrono_literals;

/* Simulate the game */

// Start going upwards
int current_heading{3}; /* Index into the position array */

class MyVec : public std::vector<int> {
 public:
  int _x, _y;
  MyVec(int a, int b) : _y{b}, _x{a} {};
  MyVec(const std::vector<int>& v) : _y{v[1]}, _x{v[0]} {}

  MyVec& operator+(const MyVec& rhs) {
    _x += rhs._x;
    _y += rhs._y;
    return *this;
  }
};

std::ostream& operator<<(std::ostream& os, const MyVec& v) {
  os << v._x << " ";
  os << v._y << " ";
  return os;
}

// clang-format off
vector<MyVec> poss{
  {1, 0},
  {0, 1},
  {-1, 0},
  {0, -1},
};
// clang-format on

using mtx = vector<vector<char>>;

bool out_of_labyrinth(mtx matrix, MyVec pos) {
  if (pos._x < 0 || pos._x > matrix.size() - 1) {
    return true;
  }

  if (pos._y < 0 || pos._y > matrix.size() - 1) {
    return true;
  }

  return false;
}

std::ostream& operator<<(std::ostream& out, const std::pair<int, int>& pair) {
  out << pair.first << " : " << pair.second;
  return out;
}
std::ostream& operator<<(std::ostream& out,
                         const std::set<std::pair<int, int>>& set) {
  if (set.empty())
    return out << "{}";
  out << "{ " << *set.begin();
  std::for_each(
      std::next(set.begin()), set.end(),
      [&out](const std::pair<int, int>& element) { out << ", " << element; });
  return out << " }";
}

int simulate(mtx matrix, MyVec pos) {
  /* Until we leave the matrix */
  std::set<std::pair<int, int>> i{{pos._x, pos._y}};
  // (x, y, direction)
  std::set<std::tuple<int, int, int>> prev_visited_twice{};
  while (true) {

    MyVec old_pos = pos;
    MyVec new_pos = pos + poss[current_heading];
    // std::cout << "Current heading: " << current_heading << "\n";

    if (out_of_labyrinth(matrix, new_pos)) {
      //   std::cout << prev_visited_twice.size() << "\n";
      return 0;
    }

    if (matrix[new_pos._y][new_pos._x] == '#') {
      //   std::cout << "Changing heading!!!" << "\n";
      current_heading = (current_heading + 1) % 4;
      pos = old_pos;
      continue;
    }
    const auto cur_pos = std::pair<int, int>({new_pos._x, new_pos._x});

    // std::cout << "Visited: " << i << "\n";

    if (prev_visited_twice.contains(
            {new_pos._x, new_pos._y, current_heading})) {
      // std::cout << "Pos: " << cur_pos.first << ":" << cur_pos.second
      //           << " visited twice"
      //           << "\n";
      // std::cout << prev_visited_twice.size() << "\n";

      // std::this_thread::sleep_for(1s);

      prev_visited_twice.insert({new_pos._x, new_pos._x, current_heading});
      return 1; /* Loop found */
    }

    i.insert({new_pos._x, new_pos._y});
    prev_visited_twice.insert({new_pos._x, new_pos._y, current_heading});
    /* Swap the matrix cells (moving the guard) */
    //  std::cout << "new pos: " << new_pos << "\n";
    //  std::cout << "old pos: " << old_pos << "\n";

    matrix[old_pos._y][old_pos._x] = 'X';
    matrix[new_pos._y][new_pos._x] = '^';
    pos = new_pos;
    // std::cout << matrix << "\n";

    using namespace std::chrono_literals;
    // std::this_thread::sleep_for(500ms);
  }
}

int main(int argc, char* argv[]) {

  auto lines = split_lines(argv[1]);

  auto matrix = create_matrix(lines);

  // std::cout << "Matrix: \n" << matrix << "\n";

  std::vector<int> starting_position{};

  /* Find the initial position (assume facing up) */
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      if (matrix[i][j] == '^') {
        //      std::cout << "Found the starting position!" << "\n";
        //      std::cout << i << " " << j << "\n";
        starting_position.push_back(j);
        starting_position.push_back(i);
      }
    }
  }

  int sum{0};

  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      char old = matrix[i][j];
      matrix[i][j] = '#';
      if (simulate(matrix, starting_position) == 1) {
        std::cout << "Loop found!" << "\n";
        std::cout << "i: " << i << "," << j << "\n";

        sum += 1;
      }
      matrix[i][j] = old;
      current_heading = 3;
    }
  }

  std::cout << "Roamed a total of: " << sum << "\n";

  return 0;
}
