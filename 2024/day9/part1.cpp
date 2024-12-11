// Copyright 2024 <Ole P. Orhagen>

#include "../utils.hpp"

vector<char> Xpand(vector<char> file) {
  vector<char> ret{};
  int counter{0};
  for (auto i = 0; i < file.size(); ++i) {
    int j = file[i] - 48;
    for (int k = 0; k < j; ++k) {
      char x = i % 2 == 0 ? to_string(counter)[0] : '.';
      ret.push_back(x);
    }
    i % 2 == 0 && counter++;
  }

  return ret;
}

vector<char> Compact(vector<char> xpanded) {
  // For each open space, fill from the back of the xpanded file

  // Find the first expanded value from the back of the array
  auto end_iterator = std::find_if(xpanded.rbegin(), xpanded.rend(),
                                   [](char a) { return a != '.'; });
  // Find the first integer open space at the front
  auto forward_iterator = std::find_if(xpanded.begin(), xpanded.end(),
                                       [](char a) { return a == '.'; });

  // Now fill the empty holes, using these iterators
  while (forward_iterator != xpanded.end() or end_iterator != xpanded.rend()) {
    if (std::distance(forward_iterator, xpanded.end()) +
            std::distance(end_iterator, xpanded.rend()) <=
        std::distance(xpanded.begin(), xpanded.end())) {
      return xpanded;
    }

    *forward_iterator = *end_iterator;
    forward_iterator = std::find_if(forward_iterator, xpanded.end(),
                                    [](char a) { return a == '.'; });
    *end_iterator = '.';

    end_iterator = std::find_if(end_iterator, xpanded.rend(),
                                [](char a) { return a != '.'; });
  }

  return xpanded;
}

long long int hashfunction(vector<char> v) {
  long long int hash{0};
  for (long long int i = 0; i < v.size(); ++i) {
    if (v[i] == '.')
      continue;
    hash += i * (v[i] - 48);
  }
  return hash;
}

int main(int argc, char* argv[]) {

  const string compacted_file = split_lines(argv[1])[0];

  auto x = Xpand({compacted_file.begin(), compacted_file.end()});

  auto c = Compact(x);

  std::cout << "Compacted: \n" << c << "\n";

  std::cout << "Hash: " << hashfunction(c) << "\n";

  return 0;
}
