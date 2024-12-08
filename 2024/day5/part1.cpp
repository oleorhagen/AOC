// Copyright 2024 <Ole P. Orhagen>

// This shit fugly !

#include "../utils.hpp"

#include <set>

int main(int argc, char* argv[]) {

  const auto lines = split_lines(argv[1]);

  // Rules
  std::unordered_map<int, vector<int>> rules{};

  // Updates
  std::map<int, std::set<int>> updates{};

  std::vector<int> middle_nrs{};

  for (const auto& line : lines) {
    if (line.find("|") != std::string::npos) {
      const auto _rules = split(line, '|');
      rules[std::stoi(_rules[1])].push_back(std::stoi(_rules[0]));
    }
    std::vector<int> update_vec{};
    if (line.find(",") != std::string::npos) {
      std::cout << "Got line: " << line << "\n";
      const auto _update = split(line, ',');
      std::set<int> update_pages{};
      // <page_nr, index>
      std::map<int, int> index{};
      int i{0};
      for (const auto page : _update) {
        // Collect all update_pages in an update into a set
        const int ipage = std::stoi(page);
        update_pages.insert(ipage);
        // TODO - What happens to duplicates (?)
        index[ipage] = i;
        i++;
        update_vec.push_back(ipage);
      }
      // Verify all the rules
      std::cout << "Checking update: " << line << "\n";

      for (const auto& [Y, Xs] : rules) {
        for (const auto X : Xs) {
          std::cout << "Checking rule: " << X << "|" << Y << "\n";

          if (update_pages.contains(Y) and update_pages.contains(X)) {
            // The index of X must be less than the index of Y
            if (index[X] > index[Y]) {
              std::cout << "NOOOO: " << line << "\n";
              std::cout << "X: " << X << " Y: " << Y << "\n";
              std::cout << "Index[X]: " << index[X] << " Index[Y]: " << index[Y]
                        << "\n";

              // exit(1);
              goto next_line;
            }
          }
        }
        // Successfully validated update
      }
      middle_nrs.push_back(update_vec[update_vec.size() / 2]);
      std::cout << "Exit after first" << "\n";
    }
  next_line:
  }

  // Print the rules
  std::cout << "Middle nrs: " << "\n";

  int sum{0};
  for (const auto& val : middle_nrs) {
    std::cout << val << "\n";
    sum += val;
  }

  std::cout << "Tot: " << sum << "\n";

  return 0;
}
