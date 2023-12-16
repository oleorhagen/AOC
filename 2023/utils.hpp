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
	T a {};
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


vector<vector<char>> create_matrix(vector<string> lines) {
	vector<vector<char>> m {};
	for (int i = 0; i < lines.size(); i++) {
		vector<char> cs(lines[0].size());
		lines[i].copy(&cs[0], cs.size());
		m.push_back(cs);
	}
	return m;
}

// TODO - Maybe return an iterator instead
// template <typename T>
// vector<T> tokenize(string s, std::function<T(string)> f) {
// 	return T {};
// }
