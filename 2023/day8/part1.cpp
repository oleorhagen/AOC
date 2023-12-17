#include "../utils.hpp"

using std::map;
using std::pair;
using std::vector;

using storage = map<string, pair<string, string>>;

storage parse_coordinates(vector<string> lines) {
	std::regex line_regex(
		"([A-Z]{3}) = \\(([A-Z]{3}), ([A-Z]{3})\\)", std::regex_constants::ECMAScript);
	storage m {};
	for (const auto &line : lines) {
		std::smatch match {};
		assert(std::regex_search(line, match, line_regex));
		string coord = match[1];
		string first_coord = match[2];
		std::regex_search(line, match, line_regex);
		string second_coord = match[3];
		m[coord] = {first_coord, second_coord};
	}
	return m;
}

void solve(string filename) {
	auto lines = split_lines(filename);
	assert(lines.size() > 1);

	vector<char> instructions = tokenize<char>(lines[0]);

	vector<string> coordinates {};
	std::copy(lines.begin() + 2, lines.end(), std::back_inserter(coordinates));

	auto m = parse_coordinates(coordinates);

	bool eof {false};
	int i {0};
	string current_pos = "AAA";

	while (not eof) {
		// Play the game
		char next_move = instructions[i++ % instructions.size()];
		string left, right;
		std::tie(left, right) = m[current_pos];
		assert(left.size() == 3);
		assert(right.size() == 3);
		if (next_move == 'L') {
			current_pos = left;
		} else {
			current_pos = right;
		}
		std::cerr << "Current pos: " << current_pos << std::endl;
		if (current_pos == "ZZZ") {
			eof = true;
		}
	}
	std::cout << "i: " << std::to_string(i) << std::endl;
}

int main(int argc, char *argv[]) {
	solve(argv[1]);
	return 0;
}
