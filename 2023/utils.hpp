#include <algorithm>
#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using std::string;
using std::vector;

vector<string> split_lines(string filename) {
	std::ifstream fs(filename);
	assert(fs);
	vector<string> lines {};
	string line {};
	while (std::getline(fs, line)) {
		lines.push_back(line);
	}
	return lines;
}

vector<string> split(string s, char delimeter) {
	std::stringstream ss {s};
	vector<string> tokens {};
	string line {};
	while (std::getline(ss, line, delimeter)) {
		tokens.push_back(line);
	}
	return tokens;
}

template <typename T>
vector<T> tokenize(string s) {
	vector<T> v {};
	int a {};
	std::stringstream ss(s);
	while (ss >> a) {
		v.push_back(a);
	}
	return v;
}

std::ostream &operator<<(std::ostream &os, const vector<int> &v) {
	for (const auto i : v) {
		os << i << " ";
	}
	return os;
}

// TODO - Maybe return an iterator instead
// template <typename T>
// vector<T> tokenize(string s, std::function<T(string)> f) {
// 	return T {};
// }
