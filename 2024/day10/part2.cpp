// -*- mode: c++; compile-command: "g++ -g -std=c++23 part2.cpp" -*-

// Copyright 2024 <Ole P. Orhagen>

#include "../utils.hpp"

using matrix = vector<vector<int>>;

int DFS(const matrix& m, int x, int y, int end_value,
        std::set<std::pair<int, int>> visited) {
  visited.insert({x, y});
  std::cout << "Current val: " << m[x][y] << "\n";

  if (m[x][y] == end_value) {
    std::cout << "Reached a peak!!" << "\n";
    return 1;
  }

  auto in_matrix_range = [&](auto pair) {
    if (pair.first < 0 || pair.second < 0) {
      return false;
    }
    if (pair.first >= m.size() || pair.second >= m.size()) {
      return false;
    }
    return true;
  };

  int sum{0};
  for (const auto& neighbour :
       neighbour4(m, x, y) | std::views::filter(in_matrix_range)) {
    if (visited.contains({neighbour.first, neighbour.second})) {
      continue;
    }
    std::cout << "Neighbour: " << neighbour
              << " val: " << m[neighbour.first][neighbour.second] << "\n";

    if (m[neighbour.first][neighbour.second] == m[x][y] + 1) {
      std::cout << "Going from: " << x << ":" << y << " -> " << neighbour
                << "\n";

      auto res = DFS(m, neighbour.first, neighbour.second, end_value, visited);
      sum += res;
    }
  }
  std::cout << "Going back up!" << "\n";

  return sum;
}

int main(int argc, char* argv[]) {

  const auto lines = split_lines(argv[1]);

  const auto m = parse_matrix<int>(lines);

  std::vector<std::pair<int, int>> starting_pos{};

  // Find the starting point (0)
  for (auto i = 0; i < m[0].size(); ++i) {
    for (auto j = 0; j < m.size(); ++j) {
      if (m[i][j] == 0) {
        starting_pos.push_back({i, j});
      }
    }
  }

  std::cout << "Starting pos size: " << starting_pos.size() << "\n";

  std::cout << "Starting pos: " << starting_pos << "\n";

  std::cout << m << "\n";

  int tot{0};

  std::set<std::pair<int, int>> visited{};

  // std::cout << "Starting at: " << starting_pos[0] << "\n";

  // auto peaks = DFS(m, m.size() - 1, 2, 0, visited);

  // std::cout << "Reached peaks: " << peaks << "\n";

  for (const auto& start_pos : starting_pos) {
    // Do a DFS search through the matrix
    int reached = DFS(m, start_pos.first, start_pos.second, 9, visited);
    std::cout << "Reached " << reached << " for " << start_pos << "\n";

    tot += reached;

    visited = {};
  }

  std::cout << "Total tops reached: " << tot << "\n";

  return 0;
}
