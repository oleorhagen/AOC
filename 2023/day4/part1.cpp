#include "../utils.hpp"



void solve(string filename) {
	int tot_score {0};
	for (auto card : split_lines(filename)) {
		auto l = split(card, ':');
		auto numbers = split(l[1], '|');
		auto winning_numbers = tokenize<int>(numbers[0]);
		auto lottery_numbers = tokenize<int>(numbers[1]);
		std::sort(winning_numbers.begin(), winning_numbers.end());
		std::sort(lottery_numbers.begin(), lottery_numbers.end());
		std::cerr << "Winning numbers: " << winning_numbers << std::endl;
		std::cerr << "Lottery numbers: " << lottery_numbers << std::endl;
		// std::unordered_set<int> a {winning_numbers.begin(), winning_numbers.end()};
		// std::unordered_set<int> b {lottery_numbers.begin(), lottery_numbers.end()};
		vector<int> v {};
		std::set_intersection(
			lottery_numbers.cbegin(),
			lottery_numbers.cend(),
			winning_numbers.cbegin(),
			winning_numbers.cend(),
			std::back_inserter(v));

		std::cerr << "intersection size: " << v.size() << std::endl;
		tot_score += 1 << (v.size() -1);
		std::cerr << " tot_score: " << tot_score << std::endl;
	}
}

int main(int argc, char *argv[]) {
	solve(argv[1]);
	return 0;
}
