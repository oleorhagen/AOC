//
// Copyright 2024 <Ole P. Orhagen>
//

#include "../utils.hpp"

// vector<char> ops(
//     int index = 0,
//     vector<std::function<long long int(long long int, long long int)>> v) {

//   const std::vector<std::function<long long int(long long int, long long int)>>
//       ops_v = {std::plus<int>{}, std::multiplies<int>{}};

//   if (index == ops_v.size() - 1) {
//     return {};
//   }
//   // Prepopulate the array
//   for (int i = 0; i < ops_v.size(); i++) {
//     v[index] = ops_v[i];
//   }
//   return {};
// }

size_t concatenationOperator(size_t a, size_t b) {
  // Return the concatenation of the two numbers
  size_t temp = b;
  do {
    temp /= 10;
    a *= 10;
  } while (temp > 0);
  return a + b;
}

size_t correctSumRecursive(vector<int> v, size_t expected_result) {
  return 0;
}

size_t correctSum(vector<int> v, size_t expected_result) {
  const std::vector<std::function<size_t(size_t, size_t)>> ops = {
      std::plus<size_t>{}, std::multiplies<size_t>{}, concatenationOperator};

  // We need to collect the sums as we go.
  vector<size_t> sums{v[0]};
  for (int i = 1; i < v.size(); i++) {
    vector<size_t> tmp_sums{};
    for (int j = 0; j < sums.size(); j++) {
      for (int k = 0; k < ops.size(); k++) {
        // std::cout << "Sums: " << sums << "\n";
        // string op = k == 0 ? " + " : " * ";
        // std::cout << "Summing: sum: " << sums[j] << op << v[i] << "\n";

        tmp_sums.push_back(ops[k](sums[j], v[i]));
      }
    }
    // std::cout << "Resetting sums to: " << tmp_sums << "\n";

    sums = tmp_sums;
  }
  // Check if the expected sum is in the sums vector
  for (const auto& sum : sums) {
    // std::cout << "Sum: " << sum << "\n";

    if (sum == expected_result) {
      std::cout << expected_result << ": " << v << "\n";
      return sum;
    }
  }
  return 0;
}

int main(int argc, char* argv[]) {

  const auto lines = split_lines(argv[1]);

  // Generate the operations vector

  size_t sum{0};

  for (const auto& line : lines) {
    // Operations
    const auto& l = split(line, ':');

    assert(l.size() == 2);

    const size_t test_value = std::stoll(l[0]);
    const vector<int> vals = tokenize<int>(l[1]);
    // std::cout << "Vs: " << vals << "\n";

    sum += correctSum(vals, test_value);
  }

  std::cout << "Sum: " << sum << "\n";

  return 0;
}
