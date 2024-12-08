// Copyright 2024 <Ole P. Orhagen>

// Now fix the incorrect updates

#include "../utils.hpp"

#include <set>

int index_of(const std::vector<int>& arr, const int& val) {
  return std::distance(arr.begin(), std::find(arr.begin(), arr.end(), val));
}

bool correct_update(std::vector<int> update,
                    std::vector<std::pair<int, int>> rules) {
  std::set<int> pages{update.begin(), update.end()};
  for (const auto rule : rules) {
    int X = rule.first;
    int Y = rule.second;
    if (pages.contains(X) and pages.contains(Y)) {
      // The ordering needs to be right
      int X_index = index_of(update, X);
      int Y_index = index_of(update, Y);
      if (X_index > Y_index) {
        return false;
      }
    }
  }
  return true;
}

std::vector<int> corrected_update(std::vector<int> update,
                                  std::vector<std::pair<int, int>> rules) {
  // Go through each update, and if a rule is broken, we swap the numbers
  std::set<int> pages{update.begin(), update.end()};
  for (const auto rule : rules) {
    int X = rule.first;
    int Y = rule.second;
    if (pages.contains(X) and pages.contains(Y)) {
      // The ordering needs to be right
      int X_index = index_of(update, X);
      int Y_index = index_of(update, Y);
      if (X_index > Y_index) {
        std::cout << "Swapping: " << X << " AND " << Y << "\n";

        std::swap(update[X_index], update[Y_index]);
      }
    }
  }
  return update;
}

int main(int argc, char* argv[]) {

  const auto lines = split_lines(argv[1]);

  // Rules
  std::vector<std::pair<int, int>> rules{};

  // Updates
  std::vector<std::vector<int>> updates{};

  std::vector<int> middle_nrs{};

  // Parse the input
  for (const auto& line : lines) {
    if (line.find("|") != std::string::npos) {
      const auto _rules = split(line, '|');
      rules.push_back({std::stoi(_rules[0]), std::stoi(_rules[1])});
    }
    if (line.find(",") != std::string::npos) {
      auto update = splitint(line, ',');
      updates.push_back(update);
    }
  }

  // Verify the updates
  for (const auto& [X, Y] : rules) {
    std::cout << X << " " << Y << "\n";
  }
  for (const auto update : updates) {
    std::cout << update << "\n";
    if (not correct_update(update, rules)) {
      std::cout << update << " Is not correct!" << "\n";

      std::vector<int> _corrected_update = corrected_update(update, rules);
      std::cout << "Corrected: " << _corrected_update << "\n";
      middle_nrs.push_back(_corrected_update[update.size() / 2]);
      std::cout << "Middle nr: " << _corrected_update[update.size() / 2]
                << "\n";
    }
  }

  int sum{0};
  for (const auto& val : middle_nrs) {
    std::cout << val << "\n";
    sum += val;
  }

  std::cout << "Tot: " << sum << "\n";

  return 0;
}
