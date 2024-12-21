// -*- mode: c++; compile-command: "g++ -g -std=c++23 part1.cpp" -*-

// Copyright 2024 <Ole P. Orhagen>

#include "../utils.hpp"

using matrix = vector<vector<char>>;
using pos = std::tuple<int, int>;

// INPROGRESS - Calculate the perimeter for a given set of cells

vector<std::pair<int, int>> neighbour4(pos p) {
  return neighbour4(std::get<0>(p), std::get<1>(p));
}

// int validNeighbours
vector<pos> validNeighbours(matrix m, pos p) {
  vector<pos> valid{};
  for (const auto& neighbour :
       neighbour4(p) |
           std::views::filter(inMatrixRange<std::pair<int, int>>(m.size())) |
           std::views::filter([&](auto next) {
             return m[std::get<0>(next)][std::get<1>(next)] ==
                    m[std::get<0>(p)][std::get<1>(p)];
           })) {
    valid.push_back(neighbour);
  }
  return valid;
}

template <typename ForwardIterator>
int perimeter(matrix m, ForwardIterator positions) {

  int total_perimeter{0};
  for (const auto& pos : positions) {
    total_perimeter += 4 - validNeighbours(m, pos).size();
  }

  return total_perimeter;
}

template <typename Container>
int area(Container positions) {
  return positions.size();
}

std::set<pos> fillArea(matrix m, pos starting_pos, std::set<pos> visited = {}) {
  std::queue<pos> frontier{{starting_pos}};

  for (; not frontier.empty(); frontier.pop()) {
    auto current_position = frontier.front();
    if (visited.contains(current_position)) {
      continue;
    }
    auto neighbours = validNeighbours(m, current_position);
    std::for_each(neighbours.begin(), neighbours.end(),
                  [&](auto n) { frontier.push(n); });
    visited.insert(current_position);
  }

  return visited;
}

std::set<std::set<pos>> filledAreas(matrix m, pos starting_pos = {0, 0}) {
  std::set<std::set<pos>> areas{};
  std::set<pos> visited{};
  for (auto i = 0; i < m.size(); ++i) {
    for (auto j = 0; j < m[0].size(); ++j) {
      areas.insert(fillArea(m, {i, j}, visited));
    }
  }
  return areas;
}

int main(int argc, char* argv[]) {

  auto m = parse_matrix<char>(split_lines(argv[1]), tokenize<char>);

  auto all_areas = filledAreas(m, {0, 0});

  size_t tot{0};
  for (auto areal : all_areas) {
    tot += perimeter(m, areal) * area(areal);
  }

  std::cout << "Tot: " << tot << "\n";

  return 0;
}
