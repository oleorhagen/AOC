
#include "../utils.hpp"

int distance_travelled(int t_tot, int t_load) {
	return t_load * (t_tot - t_load);
}

void solve(string filename) {
	vector<string> lines = split_lines(filename);
	assert(lines.size() == 2);

	vector<int> time = tokenize<int>(split(lines.at(0), ':').at(1));
	// assert(time.size() == 3);
	vector<int> distance = tokenize<int>(split(lines.at(1), ':').at(1));
	// assert(distance.size() == 3);

	std::cerr << "Wait two load time distance: " << std::endl;
	std::cerr << std::to_string(distance_travelled(7, 2)) << std::endl;

	int tot_sum {1};

	for (int i = 0; i < time.size(); i++) {
		int n_further_distances {0};
		for (int t = 0; t < time[i]; t++) {
			auto dt = distance_travelled(time[i], t);
			if (dt > distance[i]) {
				n_further_distances += 1;
			}
		}
		tot_sum *= n_further_distances;
	}
	std::cerr << "Got number: " << std::endl;
	std::cout << tot_sum << std::endl;
}

int main(int argc, char *argv[]) {
	solve(argv[1]);
	return 0;
}
