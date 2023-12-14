#include "../utils.hpp"

using matrix = vector<vector<char>>;

bool is_symbol(char c) {
	return c != '.' && not std::isdigit(c);
}

enum class Direction {
	Left,
	Right,
};

string expand(matrix m, int i, int j, Direction dir) {
	vector<char> v {};
	try {
		while (std::isdigit(m[i].at(j))) {
			v.push_back(m[i][j]);
			dir == Direction::Left ? j-- : j++;
		}
	} catch (...) {
	}
	if (v.size() > 0) {
		if (dir == Direction::Left) {
			std::reverse(v.begin(), v.end());
		}
		std::cerr << "Expand showing: " << string(v.begin(), v.end()) << std::endl;
		return string(v.cbegin(), v.cend());
	}
	std::cerr << "Returning empty string: " << std::endl;
	return "";
}

vector<int> c2iv(vector<char> v) {
	return {};
}

vector<int> get_neigh(matrix m, int i, int j) {
	try {
		if (m.at(i)[j]) {
			if (std::isdigit(m[i][j])) {
				// expand in both direction for the number
				std::cerr << "is middle number" << std::endl;
				auto s = expand(m, i, j - 1, Direction::Left) + string(1, m[i][j])
						 + expand(m, i, j + 1, Direction::Right);
				return {std::atoi(s.c_str())};
			} else {
				return {
					std::atoi(expand(m, i, j - 1, Direction::Left).c_str()),
					std::atoi(expand(m, i, j + 1, Direction::Right).c_str())};
			}
		}
	} catch (...) {
	};
	return {};
}


vector<int> get_neigh_nums(matrix m, int i, int j) {
	vector<int> all_neighbours {};
	// top
	auto top_neigh = get_neigh(m, i - 1, j);
	std::cerr << "Got top neighbour: " << top_neigh << std::endl;
	all_neighbours.insert(std::begin(all_neighbours), std::begin(top_neigh), std::end(top_neigh));
	// middle
	all_neighbours.push_back(std::atoi(expand(m, i, j - 1, Direction::Left).c_str()));
	all_neighbours.push_back(std::atoi(expand(m, i, j + 1, Direction::Right).c_str()));
	// bottom
	auto bottom_neigh = get_neigh(m, i + 1, j);
	all_neighbours.insert(
		std::begin(all_neighbours), std::begin(bottom_neigh), std::end(bottom_neigh));
	return all_neighbours;
}

void solve(string filename) {
	auto mat = create_matrix(split_lines(filename));
	int sum = 0;
	for (int i = 0; i < mat.size(); i++) {
		for (int j = 0; j < mat[0].size(); j++) {
			if (is_symbol(mat[i][j])) {
				std::cerr << "i: " << i << " j: " << j << std::endl;
				std::cerr << "Found symbol: " << mat[i][j] << std::endl;
				auto neighs = get_neigh_nums(mat, i, j);
				sum += std::accumulate(neighs.cbegin(), neighs.cend(), 0);
				std::cerr << "Found neighbours: " << neighs << std::endl;
			}
		}
	}
	std::cerr << "Result: " << std::endl;
	std::cout << sum << std::endl;
	return;
}


int main(int argc, char *argv[]) {
	solve(argv[1]);
	return 0;
}
