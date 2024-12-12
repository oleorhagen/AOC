// Copyright 2024 <Ole P. Orhagen>

#include "../utils.hpp"

#include <set>
#include <thread>

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

int simulate(mtx matrix, MyVec pos) {
  /* Until we leave the matrix */
  std::set<std::pair<int, int>> i{{pos._x, pos._y}};
  while (true) {

    MyVec old_pos = pos;
    MyVec new_pos = pos + poss[current_heading];
    std::cout << "Current heading: " << current_heading << "\n";

    if (out_of_labyrinth(matrix, new_pos)) {
      return i.size();
    }

    if (matrix[new_pos._y][new_pos._x] == '#') {
      std::cout << "Changing heading!!!" << "\n";
      current_heading = (current_heading + 1) % 4;
      pos = old_pos;
      continue;
    }
    i.insert({new_pos._x, new_pos._y});
    /* Swap the matrix cells (moving the guard) */
    std::cout << "new pos: " << new_pos << "\n";
    std::cout << "old pos: " << old_pos << "\n";

    matrix[old_pos._y][old_pos._x] = '.';
    matrix[new_pos._y][new_pos._x] = '^';
    pos = new_pos;
    std::cout << matrix << "\n";

    using namespace std::chrono_literals;
    // std::this_thread::sleep_for(500ms);
  }
}

int main(int argc, char* argv[]) {

  auto lines = split_lines(argv[1]);

  auto matrix = create_matrix(lines);

  std::cout << "Matrix: \n" << matrix << "\n";

  std::vector<int> starting_position{};

  /* Find the initial position (assume facing up) */
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      if (matrix[i][j] == '^') {
        std::cout << "Found the starting position!" << "\n";
        std::cout << i << " " << j << "\n";
        starting_position.push_back(j);
        starting_position.push_back(i);
      }
    }
  }

  int cells = simulate(matrix, starting_position);

  std::cout << "Roamed a total of: " << cells << "\n";

  return 0;
}
