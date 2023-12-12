#include "../utils.hpp"



void solve(string filename) {
	auto lines = split_lines(filename);
	size_t nr_cards = lines.size();
	std::vector<int> cards(nr_cards); // Should be zero initialized
									  // Initialize the vector to one
	for (int i = 0; i < cards.size(); i++) {
		cards[i] = 1;
	}
	int i = 0;
	for (auto card : lines) {
		auto l = split(card, ':');
		auto numbers = split(l[1], '|');
		auto winning_numbers = tokenize<int>(numbers[0]);
		auto lottery_numbers = tokenize<int>(numbers[1]);
		std::sort(winning_numbers.begin(), winning_numbers.end());
		std::sort(lottery_numbers.begin(), lottery_numbers.end());
		std::cerr << "Winning numbers: " << winning_numbers << std::endl;
		std::cerr << "Lottery numbers: " << lottery_numbers << std::endl;
		vector<int> v {};
		std::set_intersection(
			lottery_numbers.cbegin(),
			lottery_numbers.cend(),
			winning_numbers.cbegin(),
			winning_numbers.cend(),
			std::back_inserter(v));

		std::cerr << "intersection size: " << v.size() << std::endl;
		std::cerr << "iteration: " << i + 1 << std::endl;
		for (int k = 1; k <= std::min(v.size(), cards.size()); k++) {
			cards[i + k] += cards[i];
		}
		i++;
		std::cerr << cards << std::endl;
	}
	std::cout << std::accumulate(cards.cbegin(), cards.cend(), 0) << std::endl;
}

int main(int argc, char *argv[]) {
	solve(argv[1]);
	return 0;
}
