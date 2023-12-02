#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <utility>



std::pair<int, int> process_line(std::string line) {
	std::vector<int> v {};
	std::for_each(line.cbegin(), line.cend(), [&v](char a) {
		if (std::atoi(&a)) {
			v.push_back(atoi(&a));
		}
	});


	// for (int a : v) {
	// 	std::cout << "got int: " << a << std::endl;
	// }

	// Return the first and the last digit;

	int a = v[0];
	int b = v[v.size() - 1];

	std::cout << "Got a: " << a << " b: " << b << std::endl;

	return std::pair(a, b);
}


void solve(std::string fname) {
	std::ifstream file(fname);
	std::string line {};

	std::vector<int> nrs {};

	while (std::getline(file, line)) {
		auto tuple = process_line(line);
		nrs.push_back(tuple.first * 10 + tuple.second);
	}

	int count {0};
	std::for_each(nrs.cbegin(), nrs.cend(), [&count](int n) { count += n; });
	std::cout << " Got final nr: " << count << std::endl;
}

int main(int argc, char *argv[]) {
	solve(argv[1]);
	return 0;
}
