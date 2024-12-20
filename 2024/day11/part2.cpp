// -*- mode: c++; compile-command: "g++ -g -std=c++23 part2.cpp" -*-

// Copyright 2024 <Ole P. Orhagen>

#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
#include "../utils.hpp"

// Soo, doing it all at once is way too slow. Let's divide and conquer some,
// all the calculations are independent, so might as well

using key_type = std::tuple<vector<size_t>, int, int>;
using value_type = size_t;

std::map<key_type, value_type> cache{};

size_t nrOfDigits(size_t a) {
  size_t digits{0};
  for (; a / 10 != 0; a = a / 10) {
    digits += 1;
  }
  return digits + 1;
}

std::pair<size_t, size_t> splitEvenDigits(size_t a) {
  size_t length = nrOfDigits(a) / 2;
  size_t divisor = size_t(std::pow(10, length));
  size_t x = a / divisor;
  size_t y = a % divisor;
  return {x, y};
}

size_t expand(const vector<size_t> line, int depth, int max_depth) {

  if (cache.contains({line, depth, max_depth})) {
    return cache.at({line, depth, max_depth});
  }

  // std::cout << "Expanded to: " << line << " depth: " << depth << "\n";

  if (depth == max_depth) {
    return 1;
  }

  size_t tot{0};

  // For each number, produce
  for (auto i = 0; i < line.size(); ++i) {
    if (line[i] == 0) {
      auto sum = expand({1}, depth + 1, max_depth);
      tot += sum;
    } else if (nrOfDigits(line[i]) % 2 == 0) {
      auto p = splitEvenDigits(line[i]);
      auto first_sum = expand({p.first}, depth + 1, max_depth);
      auto second_sum = expand({p.second}, depth + 1, max_depth);
      tot += first_sum + second_sum;
    } else {
      auto sum = expand({line[i] * 2024}, depth + 1, max_depth);
      tot += sum;
    }
  }

  cache[{line, depth, max_depth}] = tot;
  return tot;
}

int main(int argc, char* argv[]) {

  assert(nrOfDigits(1000) == 4);
  bool even = splitEvenDigits(253000) == std::pair<size_t, size_t>{253, 0};
  assert(even);

  vector<size_t> line{};
  for (auto i = 2; i < argc; ++i) {
    line.push_back(std::atoi(argv[i]));
  }

  size_t tot{0};
  int max_depth = std::atoi(argv[1]);
  tot = expand(line, 0, max_depth);

  std::cout << "Sum: " << tot << "\n";

  return 0;
}
