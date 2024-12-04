// Copyright 2024 <Ole P. Orhagen>

#include "../utils.hpp"

/* Same as part 1. Except we allow one bad block */

vector<int> diff(vector<int> ns) {
  vector<int> v{};
  for (int i = 1; i < ns.size(); i++) {
    v.push_back(ns.at(i) - ns.at(i - 1));
  }
  return v;
}

/* Generate the list with one element missing */
vector<vector<int>> gen_list_ids(vector<int> v) {
  vector<vector<int>> vs{};
  for (int i = 0; i < v.size(); i++) {
    vector<int> tmp{};
    for (int j = 0; j < v.size(); j++) {
      if (i == j) {
        continue;
      }
      tmp.push_back(v[j]);
    }
    vs.push_back(tmp);
  }
  return vs;
}

bool is_safe(vector<int> v) {

  bool safe{false};

  std::cout << "Vector: " << v << std::endl;
  auto d = diff(v);

  std::cout << "Diff: " << d << std::endl;
  if (d.size() == 0) {
    return false;
  }

  // 1. All levels must be increasing, or decreasing. Hence they must be
  // monotonic
  if (mstd::all_of(
          d, [](int a) { return std::abs(a) >= 1 && std::abs(a) <= 3; })) {
    std::cout << d << " is safe! " << std::endl;
    if (mstd::all_of(d, [](int a) { return a < 0; }) ||
        mstd::all_of(d, [](int a) { return a > 0; })) {
      return true;
    }
  }
  return false;
}

int main(int argc, char* argv[]) {
  std::ifstream fs(argv[1]);

  if (!fs) {
    return 1;
  }

  int sum{0};

  while (fs) {
    string s;
    std::getline(fs, s);
    vector<int> v = tokenize<int>(s);

    /* Idea - If unsafe, remove a number, and run again */
    auto all_sub_lists = gen_list_ids(v);
    if (std::any_of(all_sub_lists.cbegin(), all_sub_lists.cend(), is_safe)) {
      sum += 1;
    }
  }

  std::cout << "Tot: " << sum << std::endl;

  return 0;
}
