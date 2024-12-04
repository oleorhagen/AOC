// Copyright 2024 <Ole P. Orhagen>

#include "../utils.hpp"

vector<int> diff(vector<int> ns) {
  vector<int> v{};
  for (int i = 1; i < ns.size(); i++) {
    v.push_back(ns.at(i) - ns.at(i - 1));
  }
  return v;
}

int main(int argc, char* argv[]) {

  std::ifstream fs(argv[1]);

  if (not fs) {
    return 1;
  }

  int sum{0};

  while (fs) {
    string s;
    std::getline(fs, s);
    vector<int> v = tokenize<int>(s);

    std::cout << "Vector: " << v << std::endl;
    auto d = diff(v);

    std::cout << "Diff: " << d << std::endl;
    if (d.size() == 0) {
      continue;
    }

    // 1. All levels must be increasing, or decreasing. Hence they must be monotonic

    if (mstd::all_of(
            d, [](int a) { return std::abs(a) >= 1 && std::abs(a) <= 3; })) {

      std::cout << d << " is safe! " << std::endl;
      if (mstd::all_of(d, [](int a) { return a < 0; }) or
          mstd::all_of(d, [](int a) { return a > 0; })) {

        sum += 1;
      }
    }

    // 2. All level diffs must be in range[1, 3]
  }

  std::cout << "Tot: " << sum << std::endl;

  return 0;
}
