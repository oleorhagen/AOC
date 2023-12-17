#include "../utils.hpp"

vector<int> diff(vector<int> ns) {
	vector<int> v {};
	for (int i = 1; i < ns.size(); i++) {
		v.push_back(std::abs(ns.at(i - 1) - ns.at(i)));
	}
	return v;
}

int f(vector<int> ns) {
	if (std::all_of(ns.cbegin(), ns.cend(), [](int a) { return a == 0; })) {
		return 0;
	}
	return ns.at(ns.size() - 1) + f(diff(ns));
}

void solve(string filename) {
	auto lines = split_lines(filename);
	int sum {0};
	for (const auto &line : lines) {
		vector<int> ns = tokenize<int>(line);
		std::cerr << "Got last num: " << to_string(f(ns)) << std::endl;
		sum += f(ns);
	}
	std::cout << to_string(sum) << std::endl;
}

int main(int argc, char *argv[]) {
	solve(argv[1]);
	return 0;
}
