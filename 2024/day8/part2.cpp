// -*- mode: c++; compile-command: "g++ -g -std=c++23 part2.cpp" -*-

// Copyright 2024 <Ole P. Orhagen>

/* TODO - This probably would be nicer as a std::valarray */

#include "../utils.hpp"

namespace internal {
//see: https://stackoverflow.com/a/16387374/4181011
template <typename T, size_t... Is>
T add_rhs_to_lhs(T t1, const T t2, std::integer_sequence<size_t, Is...>) {
  auto l = {(std::get<Is>(t1) += std::get<Is>(t2), 0)...};
  std::cout << typeid(l).name() << "\n";

  return t1;
}

template <typename T, size_t... Is>
T subtract_rhs_from_lhs(T t1, const T t2,
                        std::integer_sequence<size_t, Is...>) {
  auto l = {(std::get<Is>(t1) -= std::get<Is>(t2), 0)...};

  return t1;
}

template <typename T, size_t... Is>
T multiply(T t1, const int factor, std::integer_sequence<size_t, Is...>) {
  auto l = {(std::get<Is>(t1) *= factor, 0)...};
  return t1;
}

template <typename T, size_t... Is>
T divide(T t1, const int factor, std::integer_sequence<size_t, Is...>) {
  auto l = {(std::get<Is>(t1) /= factor, 0)...};
  return t1;
}

}  // namespace internal

template <typename... T>
class Vector : public std::tuple<T...> {

 public:
  using std::tuple<T...>::tuple;

  Vector operator+(const Vector& other) {
    const int size = sizeof...(T);
    return internal::add_rhs_to_lhs(*this, other,
                                    std::index_sequence_for<T...>{});
  }

  Vector operator-(const Vector& other) {
    return internal::subtract_rhs_from_lhs(*this, other,
                                           std::index_sequence_for<T...>{});
  }

  Vector operator*(const int& factor) {
    return internal::multiply(*this, factor, std::index_sequence_for<T...>{});
  }

  Vector operator/(const int& factor) {
    return internal::divide(*this, factor, std::index_sequence_for<T...>{});
  }
};

using pos = std::tuple<int, int>;

// Return the antinodes for the two given points
vector<pos> antinodes(pos _a, pos _b) {

  vector<pos> _antinodes{};

  Vector<int, int> a{std::get<0>(_a), std::get<1>(_a)};
  Vector<int, int> b{std::get<0>(_b), std::get<1>(_b)};

  // Calculate the vector between the two points
  auto dir = a - b;

  // Generate all the antinodes along the given line
  for (auto i = 0; i < 50; ++i) {
    _antinodes.push_back(a + (a - b) * i);
    _antinodes.push_back(b - (a - b) * i);
  }

  return _antinodes;
}

int main(int argc, char* argv[]) {

  Vector<int, int> a{1, 1};

  std::cout << "a: " << a << "\n";

  Vector<int, int> b = Vector<int, int>(0, 1);

  std::cout << "b: " << b << "\n";

  std::cout << "a + b: " << a + b << "\n";

  std::cout << "a - b: " << a - b << "\n";

  std::cout << "a * 2: " << a * 2 << "\n";

  std::cout << "a afterwards: " << a << "\n";

  matrix<char> m = create_matrix(split_lines(argv[1]));

  std::cout << "Matrix: \n" << m << "\n";

  std::map<char, std::vector<pos>> antennas{};

  // Collect all points (locations) of the antennas
  for (auto i = 0; i < m.size(); ++i) {
    for (auto j = 0; j < m.size(); ++j) {
      if (m[i][j] != '.') {
        antennas[m[i][j]].push_back({i, j});
      }
    }
  }

  for (const auto& [antenna, positions] : antennas) {
    std::cout << "Antenna: " << antenna << "\n";
    std::for_each(positions.begin(), positions.end(),
                  [](auto position) { std::cout << position << "\n"; });
  }

  // Create the antinodes in between the antennas by using some simple vector
  // arithmetic

  std::set<pos> all_antinodes{};

  for (const auto& [antenna, positions] : antennas) {
    for (auto i = 0; i < positions.size(); ++i) {
      for (auto j = 0; j < positions.size(); ++j) {
        if (positions[i] == positions[j]) {
          continue;
        }
        // TODO - Ideally, this should be the combinations of points
        // const auto returned_antinodes = antinodes
        const auto returned_antinodes = antinodes(positions[i], positions[j]);
        all_antinodes.insert(returned_antinodes.begin(),
                             returned_antinodes.end());
        std::cout << "Positions: " << positions[i] << " : " << positions[j]
                  << "\n";

        visualiseGrid(m.size(),
                      returned_antinodes |
                          std::views::filter(inMatrixRange<pos>(m.size())));

        std::cout << "All nodes visualised:" << "\n";

        visualiseGrid(
            m.size(),
            all_antinodes | std::views::filter(inMatrixRange<pos>(m.size())));
      }
    }
  }

  const auto all_antinodes_in_range =
      all_antinodes | std::views::filter(inMatrixRange<pos>(m.size()));

  std::cout << "All antinodes: " << all_antinodes << "\n";

  visualiseGrid(m.size(), all_antinodes_in_range);

  std::cout << "Nr antinodes in range: " << all_antinodes_in_range.base().size()
            << "\n";

  size_t tot{0};
  for (const auto& node :
       all_antinodes | std::views::filter(inMatrixRange<pos>(m.size()))) {
    tot += 1;
  }

  std::cout << "Nr antinodes in range: " << tot << "\n";

  // std::cout << all_antinodes_in_range << "\n";

  return 0;
}
