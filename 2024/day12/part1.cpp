// -*- mode: c++; compile-command: "g++ -g -std=c++23 part1.cpp" -*-

// Copyright 2024 <Ole P. Orhagen>

#include "../utils.hpp"

int main(int argc, char* argv[]) {

  auto m = parse_matrix<char>(split_lines(argv[1]), tokenize<char>);

  std::cout << "Matrix: " << "\n";

  std::cout << m << "\n";

  return 0;
}
