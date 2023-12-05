#include "utils.hpp"

// while isdigit
/// Check all surrounding squares for symbols
/// When no longer digit multiply the number by the number of symbols found

using matrix = vector<vector<char>>;
using positions = vector<std::pair<int, int>>;

vector<vector<char>> create_matrix(vector<string> lines) {
	matrix m {};
	for (int i = 0; i < lines.size(); i++) {
		vector<char> cs(lines[0].size());
		lines[i].copy(&cs[0], cs.size());
		m.push_back(cs);
	}
	return m;
}


int get_n_symbols(matrix m, positions poss) {
	int num_symbols {0};
	for (std::pair<int, int> pos : poss) {
		try {
			// std::cerr << "pos.first: " << pos.first << " pos.second: " << pos.second <<
			// std::endl;
			char c = m.at(pos.first).at(pos.second);
			// std::cerr << "char: " << c << std::endl;
			if (c != '.' and not std::isdigit(c)) {
				num_symbols += 1;
			}
		} catch (...) {
			// std::cerr << "Caught exception" << std::endl;
		}
	}
	return num_symbols;
}

void solve(string filename) {
	std::cerr << "Filename: " << filename << std::endl;

	auto matrix = create_matrix(split_lines(filename));

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[0].size(); j++) {
			std::cerr << matrix[i][j];
		}
		std::cerr << std::endl;
	}

	int tot_sum {0};

	vector<char> cur_num {};

	int num_symbols {0};

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[0].size(); j++) {
			if (std::isdigit(matrix[i][j])) {
				// Get all symbols in the column to the left
				//
				//   x
				//   x d
				//   x
				num_symbols += get_n_symbols(matrix, {{i + 1, j - 1}, {i, j - 1}, {i - 1, j - 1}});
				// std::cerr << "i: " << i << " j: " << j << std::endl;
				// std::cerr << "num_symbols: " << num_symbols << std::endl;
				cur_num.push_back(matrix[i][j]);
			} else {
				// no digit
				//
				// collect the right end
				//
				// x x
				// d x <- we are here
				// x x
				//
				// Then multiple the current number by the number of symbols
				if (std::atoi(string(cur_num.begin(), cur_num.end()).c_str())) {
					num_symbols +=
						get_n_symbols(matrix, {{i + 1, j - 1}, {i, j - 1}, {i - 1, j - 1}});
					num_symbols += get_n_symbols(matrix, {{i + 1, j}, {i, j}, {i - 1, j}});
					std::cerr << "Num neighbouring symbols: " << num_symbols << std::endl;
					std::cerr << "Current number: " << string(cur_num.begin(), cur_num.end())
							  << std::endl;

					tot_sum +=
						(std::atoi(string(cur_num.begin(), cur_num.end()).c_str()) * num_symbols);
					std::cerr << "tot_sum: " << tot_sum << std::endl;
					cur_num = {};    // Reset
					num_symbols = 0; // Reset
				}
			}
		}
		cur_num = {};
		num_symbols = 0; // End of line
	}

	std::cout << tot_sum << std::endl;

	return;
}


int main(int argc, char *argv[]) {
	solve(argv[1]);
	return 0;
}
