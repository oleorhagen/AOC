// Copyright 2024 <Ole P. Orhagen>

#include "../utils.hpp"

int main(int argc, char* argv[]) {

  std::ifstream ifs(argv[1]);

  std::string s((std::istreambuf_iterator<char>(ifs)),
                (std::istreambuf_iterator<char>()));

  std::cout << "S: " << s << "\n";


  std::regex mul_regexp("(mul(\\d,\\d))", std::regex_constants::ECMAScript |
                                              std::regex_constants::icase);
  if (std::regex_search(s, mul_regexp))
    std::cout << "Text contains the phrase 'regular expressions'\n";

  std::regex word_regex("(mul\\((\\d{1,3},\\d{1,3})\\))");
  int submatches[]{2};
  auto words_begin =
      std::sregex_token_iterator(s.begin(), s.end(), word_regex, submatches);
  auto words_end = std::sregex_token_iterator();

  int sum{};
  for (auto i = words_begin; i != words_end; i++) {
    vector<int> nrs = splitint(*i, ',');
    std::cout << "I: " << nrs[0] << " II: " << nrs[1] << "\n";

    sum += nrs[0] * nrs[1];
  }

  std::cout << sum << "\n";

  return 0;
}
