#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <sstream>
#include <iostream>
#include <functional>

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
vector<T> tokenize(string s, std::function<T(string)> f) {
	return T {};
}
