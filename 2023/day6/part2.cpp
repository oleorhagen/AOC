#include "../utils.hpp"

int64_t distance_travelled(int64_t t_tot, int64_t t_load) {
	return t_load * (t_tot - t_load);
}

void solve(string filename) {
	vector<string> lines = split_lines(filename);
	assert(lines.size() == 2);

	vector<char> time = tokenize<char>(split(lines.at(0), ':').at(1));
	// assert(time.size() == 3);
	vector<char> distance = tokenize<char>(split(lines.at(1), ':').at(1));
	// assert(distance.size() == 3);

	// Convert to numbers
	int t = std::atoi(&time[0] + '\0');
	int64_t d {std::atol(&distance[0] + '\0')};

	std::cerr << "t: " << std::to_string(t) << std::endl;
	std::cerr << "d: " << std::to_string(d) << std::endl;


	int64_t n_further_distances {0};
	for (int i = 0; i < t; i++) {
		auto dt = distance_travelled(t, i);
		if (dt > d) {
			n_further_distances += 1;
		}
	}
	std::cerr << "Got number: " << std::endl;
	std::cout << n_further_distances << std::endl;
}

int main(int argc, char *argv[]) {
	solve(argv[1]);
	return 0;
}
