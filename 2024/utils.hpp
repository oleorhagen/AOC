#include <algorithm>
#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <ranges>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using std::string;
using std::to_string;
using std::vector;

vector<string> split_lines(string filename) {
  std::ifstream fs(filename);
  assert(fs);
  vector<string> lines{};
  string line{};
  while (std::getline(fs, line)) {
    lines.push_back(line);
  }
  return lines;
}

vector<string> split(string s, char delimeter) {
  std::stringstream ss{s};
  vector<string> tokens{};
  string line{};
  while (std::getline(ss, line, delimeter)) {
    tokens.push_back(line);
  }
  return tokens;
}

vector<int> splitint(string s, char delimeter) {
  std::stringstream ss{s};
  vector<int> tokens{};
  string line{};
  while (std::getline(ss, line, delimeter)) {
    tokens.push_back(std::stoi(line));
  }
  return tokens;
}

template <typename T>
vector<T> tokenize(string s) {
  vector<T> v{};
  T a{};
  std::stringstream ss(s);
  while (ss >> a) {
    v.push_back(a);
  }
  return v;
}

vector<int> digits(string s) {
  vector<int> digits{};
  std::regex digit_regex("([0-9])");
  int submatches[]{1};

  auto digits_begin =
      std::sregex_token_iterator(s.begin(), s.end(), digit_regex, submatches);
  auto digits_end = std::sregex_token_iterator();

  for (auto i = digits_begin; i != digits_end; i++) {
    digits.push_back(std::stoi(*i));
  }

  return digits;
}

string trim(string s) {
  std::string::iterator end_pos = std::remove(s.begin(), s.end(), ' ');
  s.erase(end_pos, s.end());
  return s;
}

std::ostream& operator<<(std::ostream& os, const vector<int>& v) {
  for (const auto i : v) {
    os << i << " ";
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const vector<long long int>& v) {
  for (const auto i : v) {
    os << i << " ";
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const vector<string>& v) {
  for (const auto i : v) {
    os << i << " ";
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const vector<char>& v) {
  for (const auto i : v) {
    os << i << " ";
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const vector<vector<char>>& v) {
  for (const auto i : v) {
    os << i << "\n";
  }
  return os;
}

vector<vector<char>> create_matrix(vector<string> lines) {
  vector<vector<char>> m{};
  for (int i = 0; i < lines.size(); i++) {
    vector<char> cs(lines[0].size());
    lines[i].copy(&cs[0], cs.size());
    m.push_back(cs);
  }
  return m;
}

namespace mstd {
template <class InputIt, class UnaryFunction>
constexpr UnaryFunction for_each(InputIt it, UnaryFunction f) {
  return std::for_each(it.cbegin(), it.cend(), f);
}

template <class InputIt, class UnaryPredicate>
constexpr bool all_of(InputIt it, UnaryPredicate p) {
  return std::find_if_not(it.cbegin(), it.cend(), p) == it.cend();
}

template <typename T>
size_t last(T t) {
  return t.size() - 1;
}

}  // namespace mstd

// TODO - Maybe return an iterator instead
// template <typename T>
// vector<T> tokenize(string s, std::function<T(string)> f) {
// 	return T {};
// }
