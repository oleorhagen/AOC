#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <optional>
#include <queue>
#include <ranges>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using std::nullopt;
using std::optional;
using std::pair;
using std::string;
using std::to_string;
using std::vector;

template <typename T>
using matrix = vector<vector<T>>;
using pos = std::tuple<int, int>;

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

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::tuple<T, T>& v) {

  os << std::get<0>(v) << ":" << std::get<1>(v) << std::endl;
  return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& v) {
  for (const auto i : v) {
    os << i << " ";
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const vector<int>& v) {
  for (const auto i : v) {
    os << i << " ";
  }
  return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& v) {
  for (const auto i : v) {
    os << i << " ";
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const vector<size_t>& v) {
  for (const auto i : v) {
    os << i << " ";
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const std::span<size_t>& v) {
  for (const auto i : v) {
    os << i << " ";
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const std::span<int>& v) {
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

std::ostream& operator<<(std::ostream& os, const vector<vector<int>>& v) {
  for (const auto i : v) {
    os << i << "\n";
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const std::pair<int, int>& p) {
  os << p.first << ":" << p.second << "\n";
  return os;
}

std::ostream& operator<<(std::ostream& os,
                         const vector<std::pair<int, int>>& v) {
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

/* TODO - Obviously, this has to handle other cases of types */
template <typename T>
vector<vector<T>> parse_matrix(
    vector<string> lines,
    std::function<vector<T>(string)> line_parser = digits) {
  vector<vector<T>> m{};
  for (int i = 0; i < lines.size(); i++) {
    vector<T> cs = line_parser(lines[i]);
    // vector<T> cs{};
    m.push_back(cs);
  }
  return m;
}

// Return the manhattan neighbour cells (only positive results)
vector<std::pair<int, int>> neighbour4(int x, int y) {
  vector<std::pair<int, int>> neigbours = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
  std::ranges::transform(neigbours.begin(), neigbours.end(), neigbours.begin(),
                         [x, y](const std::pair<int, int>& p) {
                           return std::pair<int, int>{p.first + x,
                                                      p.second + y};
                         });
  return neigbours;
}

vector<std::pair<int, int>> neighbour8(int x, int y) {
  vector<std::pair<int, int>> neigbours = {{0, 1},  {1, 1},   {1, 0},  {1, -1},
                                           {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
  std::ranges::transform(neigbours.begin(), neigbours.end(), neigbours.begin(),
                         [x, y](const std::pair<int, int>& p) {
                           return std::pair<int, int>{p.first + x,
                                                      p.second + y};
                         });
  return neigbours;
}

auto neighbour_diagonals(int x, int y) {
  const auto neighbours8 = neighbour8(x, y);
  const auto neighbours4 = neighbour4(x, y);
  std::set<std::pair<int, int>> n4{neighbours4.begin(), neighbours4.end()};
  vector<std::pair<int, int>> res{};
  for (const auto& neighbour :
       neighbours8 | std::ranges::views::filter(
                         [n4](auto p) { return not n4.contains(p); })) {
    res.push_back(neighbour);
  }
  return res;
}

template <typename pos>
std::function<bool(pos p)> inMatrixRange(size_t size) {
  return [size](pos p) {
    return std::get<0>(p) >= 0 and std::get<1>(p) >= 0 and
           std::get<0>(p) < size and std::get<1>(p) < size;
  };
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

template <typename ForwardIterator>
void visualiseGrid(size_t size, ForwardIterator fit) {
  matrix m(size, vector<char>(size));

  for (auto i = 0; i < m.size(); ++i) {
    for (auto j = 0; j < m.size(); ++j) {
      m[i][j] = '.';
    }
  }

  for (auto point : fit) {
    m[std::get<0>(point)][std::get<1>(point)] = 'X';
  }

  for (auto i = 0; i < m.size(); ++i) {
    for (auto j = 0; j < m.size(); ++j) {
      std::cerr << m[i][j];
    }
    std::cerr << "\n";
  }

  return;
}

// TODO - Maybe return an iterator instead
// template <typename T>
// vector<T> tokenize(string s, std::function<T(string)> f) {
// 	return T {};
// }

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
