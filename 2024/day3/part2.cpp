// Copyright 2024 <Ole P. Orhagen>

#include "../utils.hpp"

/* Change it to a simple multiplying state machine */

int main(int argc, char* argv[]) {

  std::ifstream ifs(argv[1]);

  std::string s((std::istreambuf_iterator<char>(ifs)),
                (std::istreambuf_iterator<char>()));

  std::regex word_regex(
      "mul\\((\\d{1,3},\\d{1,3})\\)|(do\\(\\))|(don't\\(\\))");
  int submatches[]{1, 2, 3};
  auto words_begin =
      std::sregex_token_iterator(s.begin(), s.end(), word_regex, submatches);
  auto words_end = std::sregex_token_iterator();

  int sum{};
  bool state_mul{true}; /* Starts out as false */
  for (auto i = words_begin; i != words_end; i++) {
    std::cout << "GOT : " << *i << "\n";

    if (*i == "") {
      continue;
    }

    if (*i == "do()") {
      std::cout << "DO" << "\n";

      state_mul = true;
      continue;
    }
    if (*i == "don't()") {
      std::cout << "Dont" << "\n";

      state_mul = false;
      continue;
    }
    if (state_mul) {
      vector<int> nrs = splitint(*i, ',');
      std::cout << "I: " << nrs[0] << " II: " << nrs[1] << "\n";

      sum += nrs[0] * nrs[1];
    }
  }

  std::cout << sum << "\n";

  return 0;
}
