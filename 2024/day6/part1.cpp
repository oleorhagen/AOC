// Copyright 2024 <Ole P. Orhagen>

#include "../utils.hpp"

/* Simulate the game */

// Start going upwards
int current_heading{2}; /* Index into the position array */

class MyVec : public std::vector<int> {
 public:
  int _x, _y;
  MyVec(int a, int b) : _y{b}, _x{a} {};

  MyVec& operator+(const MyVec& rhs) {
    _x += rhs._x;
    _y += rhs._y;
    return *this;
  }
};

MyVec foo{1, 0};

// clang-format off
vector<vector<int>> poss{
  {1, 0},
  {0, 1},
  {-1, 0},
  {0, -1},
};
// clang-format on

using mtx = vector<vector<char>>;

void simulate(mtx matrix, vector<int> pos) {
  /* Until we leave the matrix */
  while (true) {
    // pos + poss[current_heading];
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
        starting_position.push_back(i);
        starting_position.push_back(j);
      }
    }
  }

  return 0;
}
