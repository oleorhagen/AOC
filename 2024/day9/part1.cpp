// Copyright 2024 <Ole P. Orhagen>

#include "../utils.hpp"

using disk_map = vector<int>;

disk_map Xpand(disk_map file) {
  disk_map ret{};
  int counter{0};
  for (auto i = 0; i < file.size(); ++i) {
    int j = file[i];
    for (int k = 0; k < j; ++k) {
      int x = i % 2 == 0 ? counter : -1;
      ret.push_back(x);
    }
    i % 2 == 0 && counter++;
  }

  return ret;
}

disk_map Compact(disk_map xpanded) {
  // For each open space, fill from the back of the xpanded file

  // Find the first expanded value from the back of the array
  auto end_iterator = std::find_if(xpanded.rbegin(), xpanded.rend(),
                                   [](char a) { return a != -1; });
  // Find the first integer open space at the front
  auto forward_iterator = std::find_if(xpanded.begin(), xpanded.end(),
                                       [](char a) { return a == -1; });

  // Now fill the empty holes, using these iterators
  while (forward_iterator != xpanded.end() or end_iterator != xpanded.rend()) {
    if (std::distance(forward_iterator, xpanded.end()) +
            std::distance(end_iterator, xpanded.rend()) <=
        std::distance(xpanded.begin(), xpanded.end())) {
      return xpanded;
    }

    *forward_iterator = *end_iterator;
    forward_iterator = std::find_if(forward_iterator, xpanded.end(),
                                    [](char a) { return a == -1; });
    *end_iterator = -1;

    end_iterator = std::find_if(end_iterator, xpanded.rend(),
                                [](char a) { return a != -1; });
  }

  return xpanded;
}

long long int hashfunction(disk_map v) {
  long long int hash{0};
  for (long long int i = 0; i < v.size(); ++i) {
    if (v[i] == -1)
      return hash;
    hash += i * v[i];
  }
  return hash;
}

int main(int argc, char* argv[]) {

  const string compacted_file = split_lines(argv[1])[0];

  const disk_map m = digits(compacted_file);

  std::cout << "toknized: " << m << "\n";

  auto x = Xpand(m);

  std::cout << "xpanded: " << x << "\n";

  auto c = Compact(x);

  std::cout << "Compacted: \n" << c << "\n";

  std::cout << "Hash: " << hashfunction(c) << "\n";

  return 0;
}
