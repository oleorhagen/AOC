// -*- mode: c++; compile-command: "g++ -g -std=c++23 part1.cpp" -*-

// Copyright 2024 <Ole P. Orhagen>

#include "../utils.hpp"

// TODO - Need neighbour-4
// TODO - Need to do a BFS or DFS search on the resulting graph

using matrix = vector<vector<int>>;

int DFS(const matrix& m, int x, int y, std::set<std::pair<int, int>>& visited) {
  visited.insert({x, y});
  std::cout << "Current val: " << m[y][x] << "\n";

  if (m[y][x] == 9) {
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
              << " val: " << m[neighbour.second][neighbour.first] << "\n";

    if (m[neighbour.second][neighbour.first] == m[y][x] + 1) {
      std::cout << "Going from: " << x << ":" << y << " -> " << neighbour
                << "\n";

      auto res = DFS(m, neighbour.first, neighbour.second, visited);
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

  std::cout << "Starting pos: " << starting_pos << "\n";

  std::cout << m << "\n";

  int tot{0};

  std::set<std::pair<int, int>> visited{};

  std::cout << "Starting at: " << starting_pos[0] << "\n";

  // auto _ = DFS(m, starting_pos[0].second, starting_pos[0].first, visited);

  // Count the number of 9's in visited
  // for (const auto& pos : visited) {
  //   if (m[pos.second][pos.first] == 9) {
  //     tot += 1;
  //   }
  // }

  // Visualize the path
  // auto m_copy = m;
  // for (const auto& pos : visited) {
  //   m_copy[pos.first][pos.second] = -1;
  // }
  // std::cout << "Visualized path travelled:" << "\n";
  // std::cout << m_copy << "\n";

  for (const auto& start_pos : starting_pos) {
    // Do a DFS search through the matrix
    int reached = DFS(m, start_pos.second, start_pos.first, visited);
    std::cout << "Reached " << reached << " for " << start_pos << "\n";

    for (const auto& pos : visited) {
      if (m[pos.second][pos.first] == 9) {
        tot += 1;
      }
    }

    visited = {};
  }

  std::cout << "Total tops reached: " << tot << "\n";

  return 0;
}
