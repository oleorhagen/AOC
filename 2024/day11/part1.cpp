// -*- mode: c++; compile-command: "g++ -g -std=c++23 part1.cpp" -*-

// Copyright 2024 <Ole P. Orhagen>

#include "../utils.hpp"

// TODO - Are ints really the best representation (?)
//         Apparantly not (!)

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

vector<size_t> expand(const vector<size_t> line) {
  vector<size_t> new_line{};

  // bool is_even_digits = nrOfDigits(line[i]) % 2 == 0;

  // For each number, produce
  for (auto i = 0; i < line.size(); ++i) {
    // Check the rules
    if (line[i] == 0) {
      new_line.push_back(1);
    } else if (nrOfDigits(line[i]) % 2 == 0) {
      auto p = splitEvenDigits(line[i]);
      new_line.push_back(p.first);
      new_line.push_back(p.second);
    } else {
      // Default
      new_line.push_back(line[i] * 2024);
    }
  }

  return new_line;
}

int main(int argc, char* argv[]) {

  assert(nrOfDigits(1000) == 4);
  bool even = splitEvenDigits(253000) == std::pair<size_t, size_t>{253, 0};
  assert(even);

  vector<size_t> line{};
  for (auto i = 1; i < argc; ++i) {
    line.push_back(std::atoi(argv[i]));
  }

  // std::cout << "Parsed: " << line << "\n";

  for (auto i = 0; i < 25; ++i) {
    line = expand(line);
    std::cout << "After " << i + 1 << " blinks:" << "\n";
  }

  std::cout << "Sum: " << line.size() << "\n";

  return 0;
}
