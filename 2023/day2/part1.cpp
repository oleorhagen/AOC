#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <sstream>
#include <iostream>

using std::string;
using std::vector;

// Allowance:

// 12 red
// 13 green
// 14 blue

const int red = 12;
const int green = 13;
const int blue = 14;

// Figure out if a game constellation is possible

// Sum the IDs of the possible games

vector<string> split_lines(string filename) {
  std::ifstream fs(filename);
  assert(fs);
  vector<string> lines {};
  string line {};
  while(std::getline(fs, line)) {
    lines.push_back(line);
  }
  return lines;
}

vector<string> split(string s, char delimeter) {
  std::stringstream ss {s};
  vector<string> tokens {};
  string line {};
  while(std::getline(ss, line, delimeter)) {
    tokens.push_back(line);
  }
  return tokens;
}

enum class Color {
  Red,
  Blue,
  Green,
  Undef,
};

Color parse_colour(string colour) {
  if (colour.find("red") == 0) {
    return Color::Red;
  }
  if (colour.find("blue") == 0) {
    return Color::Blue;
  }
  if (colour.find("green") == 0) {
    return Color::Green;
  }
  return Color::Undef;
}

// trim from start (in place)
static inline void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
    return !std::isspace(ch);
  }));
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
  ltrim(s);
  return s;
}

std::pair<Color, int> parse_sample(string sample) {
  // Trim starting space
  std::cerr << "Parsing sample: " << std::endl;
  sample = ltrim_copy(sample);
  vector<string> v = split(sample, ' ');
  std::cerr << "parse_sample: " << sample << ": v: " << v.size() << std::endl;
  for (auto g: v) {
    std::cerr << "v: " << g << std::endl;
  }
  assert(v.size() == 2);

  int nr = std::atoi(&v[0].at(0));

  Color c = parse_colour(v[1]);

  return std::pair(c, nr);
}

bool allowance(std::pair<Color, int> p) {
  switch ( p.first ) {
  case Color::Red:
    return p.second <= red;
  case Color::Blue:
    return p.second <= blue;
  case Color::Green:
    return p.second <= green;
  }
  return false;
}

std::vector<std::pair<Color, int>> parse_line(string line) {
  std::cout << "Got line: " << line << std::endl;
  auto tokens = split(line, ':');
  assert(tokens.size() == 2);
  int game_id = std::atoi(&tokens[0][tokens[0].size()-1]);
  std::cout << "Game ID: " << game_id << std::endl;
  vector<string> games = split(tokens[1], ';');
  std::vector<std::pair<Color, int>> toks {};
  for (string game: games) {
    auto sample = split(game, ',');
    std::cout << "Sample: " << game << std::endl;
    vector<std::pair<Color,int>> pairs {};
    std::cerr << "transforming sample" << std::endl;
    std::transform(sample.begin(), sample.end(), std::back_inserter( pairs ),  parse_sample);
    toks.insert(toks.begin(), pairs.begin(), pairs.end());
  }
  return toks;
}

void solve(string filename) {
  auto lines = split_lines(filename);

  int i = 0;
  int id_sum = 0;
  for (string line : lines) {
    auto tokens = parse_line(line);
    ++i;
    if (std::all_of(tokens.cbegin(), tokens.cend(), [](std::pair<Color,int> v) {
      return allowance(v);
    })) {
      id_sum += i;
    }
  }
  std::cout << "Final sum: " << id_sum << std::endl;
}

int main(int argc, char *argv[])
{
  solve(argv[1]);
  return 0;
}

