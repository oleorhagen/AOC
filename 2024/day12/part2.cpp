// -*- mode: c++; compile-command: "g++ -g -std=c++23 part2.cpp" -*-

// Copyright 2024 <Ole P. Orhagen>

#include "../utils.hpp"

/* INPROGRESS - Not quite right (!) - Seems the neighbouring region fill is not quite working ! */
/* How on earth did it work for the first part? */
// Add some visuals to help debug this

/* INPROGRESS - Implement proper flood-fill */

using matrix = vector<vector<char>>;
using pos = std::tuple<int, int>;

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

vector<pos> explode(pos p) {
  vector<std::tuple<int, int>> neigbours = {{0, 1}, {0, 2}, {1, 2}, {1, 1}};
  std::ranges::transform(neigbours.begin(), neigbours.end(), neigbours.begin(),
                         [&p](const std::pair<int, int>& n) {
                           return std::tuple<int, int>{
                               n.first + std::get<0>(p),
                               n.second + std::get<1>(p)};
                         });

  std::cout << "Exploded: " << p << " to: " << neigbours << "\n";

  return neigbours;
}

template <typename ForwardIterator>
size_t numberOfSides(ForwardIterator& fit) {
  std::map<pos, uint> edges{};
  for (const auto& p : fit) {
    for (const auto& n : explode(p)) {
      edges[n] += 1;
      std::cout << "Edges: " << n << edges[n] << "\n";
    }
  }
  size_t tot_sides{0};
  for (auto [edge, count] : edges) {
    std::cout << "Edge: " << edge << " count: " << count << "\n";

    if (count % 2 != 0) {
      tot_sides += 1;
    }
  }
  std::cout << "Sides: " << tot_sides << "\n";

  return tot_sides;
}

template <typename ForwardIterator>
int perimeter(matrix m, ForwardIterator positions) {

  std::cout << "Finding the number of sides for: " << positions << "\n";
  return numberOfSides(positions);
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

template <typename ForwardIterator>
void visualise(size_t size, ForwardIterator fit) {
  matrix m(size, vector<char>(size));

  for (auto i = 0; i < m.size(); ++i) {
    for (auto j = 0; j < m.size(); ++j) {
      m[i][j] = '.';
      std::cerr << m[i][j];
    }
    std::cerr << "\n";
  }

  for (auto point : fit) {
    m[std::get<0>(point)][std::get<1>(point)] = 'X';
  }

  for (auto i = 0; i < m.size(); ++i) {
    for (auto j = 0; j < m.size(); ++j) {
      std::cerr << m[i][j];
    }
    std::cerr << "\n";
  }

  return;
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
    visualise(m.size(), areal);
    auto c = perimeter(m, areal) * area(areal);
    std::cerr << "perimeter: " << perimeter(m, areal) << "\n";
    tot += c;
  }

  std::cout << "Tot: " << tot << "\n";

  return 0;
}
