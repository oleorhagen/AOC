// -*- mode: c++; compile-command: "g++ -g -std=c++23 part1.cpp" -*-

// Copyright 2024 <Ole P. Orhagen>

#include "../utils.hpp"

constexpr size_t xmas_length = 4;

std::array<char, 4> xmas = {'X', 'M', 'A', 'S'};

int main(int argc, char* argv[]) {

  auto m = parse_matrix<char>(split_lines(argv[1]), tokenize<char>);

  size_t found{0};

  for (auto i = 0; i < m.size(); ++i) {
    for (auto j = 0; j < m.size(); ++j) {
      // Filter 1: XMAS can only start at X
      if (m[i][j] != 'X')
        continue;
      std::cout << "x: " << i << " y: " << j << "\n";

      const auto neighbours = neighbour8(i, j);
      for (auto k = 0; k < neighbours.size(); ++k) {
        // Traverse the direction
        Vector<int, int> a{i, j};
        Vector<int, int> b{neighbours[k]};
        Vector<int, int> dir = a;
        Vector<int, int> _dir = a - b;
        std::cout << "dir: " << dir << "\n";
        // We need to traverse length 4 along each vector direction
        vector<pos> word{};
        for (auto l = 0; l < xmas_length; ++l) {
          word.push_back(dir);
          dir = dir + _dir;
          std::cout << "New dir: " << dir << "\n";
        }
        // Now compare the word using the inMatrixRange filter
        auto collected_word =
            word | std::views::filter(inMatrixRange<pos>(m.size()));
        vector<char> _collected_word{};
        for (auto letter : collected_word) {
          std::cout << "Letter: " << m[std::get<0>(letter)][std::get<1>(letter)]
                    << "\n";
          _collected_word.push_back(
              m[std::get<0>(letter)][std::get<1>(letter)]);
        }
        if (std::ranges::equal(xmas, _collected_word)) {
          std::cout << "Found XMAS!" << "\n";
          found += 1;
        }
      }
    }
  }

  std::cout << "XMAS count: " << found << "\n";

  return 0;
}
