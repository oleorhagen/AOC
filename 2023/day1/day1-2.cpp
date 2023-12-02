#include <string>
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <utility>
#include <map>
#include <optional>


using std::optional;
using std::string;


// Plan of action:

// Create function which extracts the first number from a string

// Extract the number from the string, and the reversed string

// Return the number

// Add them together

std::map<std::string, int> nrs {
	{"one", 1},
	{"two", 2},
	{"three", 3},
	{"four", 4},
	{"five", 5},
	{"six", 6},
	{"seven", 7},
	{"eight", 8},
	{"nine", 9},
};

std::vector<string> nrs_v {
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine",
};


optional<int> is_number(string s, int index) {
	string sub = s.substr(index, s.size());
	for (int i = 0; i < 9; i++) {
		if (sub.find(nrs_v[i]) == 0) {
			return i + 1;
		}
	}
	return std::nullopt;
}

std::pair<int, int> number_from_string(std::string line) {
	std::vector<int> v {};

	for (int i = 0; i < line.size(); i++) {
		auto n = is_number(line, i);
		char c = line.at(i);
		if (n) {
			// We have a number or a number
			std::cout << "We got a number (text): " << n.value() << std::endl;
			v.push_back(n.value());
		} else if (std::atoi(&c)) {
			// TODO
			std::cout << "we got a number (digit): " << std::atoi(&c) << std::endl;
			v.push_back(std::atoi(&c));
		}
	}
	return std::pair(v.at(0), v.at(v.size() - 1));
}

void solve(string filename) {
	std::ifstream file(filename);
	assert(file);

	int sol {0};

	string line {};
	while (std::getline(file, line)) {
		std::cout << line << std::endl;
		auto n = number_from_string(line);
		std::cout << "extracted: " << std::endl;
		std::cout << "a: " << n.first << " b: " << n.second << std::endl;
		sol += n.first * 10 + n.second;
	}

	std::cout << "Res: " << std::endl;
	std::cout << sol << std::endl;
}

int main(int argc, char *argv[]) {
	solve(argv[1]);
	return 0;
}
