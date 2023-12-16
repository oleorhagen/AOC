#include "../utils.hpp"

// Five of a kind
// Four of a kind
// three of a kind
// Two pair
// two of a kind
// no matches (high card)

// Need a function which takes the hand and returns an integer to sort this

using hand = vector<char>;

std::map<char, int> card_value = {
	{'A', 15},
	{'K', 14},
	{'Q', 13},
	{'J', 12},
	{'T', 11},
	{'9', 9},
	{'8', 8},
	{'7', 7},
	{'6', 6},
	{'5', 5},
	{'4', 4},
	{'3', 3},
	{'2', 2},
	{'1', 1},
};

int hand_value(hand h) {
	std::map<char, int> m {};
	for (const auto &c : h) {
		m[c] += 1;
	}
	int hand_val {0};
	for (const auto &[key, val] : m) {
		hand_val = std::max(hand_val, val);
	}
	switch (hand_val) {
	case 5:
		return 6;
	case 4:
		return 5;
	case 3: {
    int c{0};
		for (const auto &a : m | std::views::values) {
			if (a == 2) {
        return 4;
			}
		}
    return 3;
  }
	case 2: {
		int c {0};
		for (const auto &a : m | std::views::values) {
			if (a == 2) {
				c += 1;
				if (c == 2) {
					return 2;
				}
			}
		}
		return 1;
	}
	case 1:
		return 0;
	}
	assert(false);
}

std::ostream &operator<<(std::ostream &os, const vector<char> &v) {
	for (const auto i : v) {
		os << '\'' << i << '\'' << " ";
	}
	return os;
}

bool cmp_fn_secondary(const hand &h1, const hand &h2) {
	for (int i = 0; i < h1.size(); i++) {
		if (card_value[h1.at(i)] == card_value[h2.at(i)]) {
			continue;
		}
		if (card_value[h1.at(i)] < card_value[h2.at(i)]) {
			return true;
		}
		return false;
	}
	return false;
}

bool cmp_fn(const hand &h1, const hand &h2) {
	int h1_val = hand_value(h1);
	int h2_val = hand_value(h2);
	if (h1_val < h2_val) {
		return true;
	}
	if (h1_val == h2_val) {
		return cmp_fn_secondary(h1, h2);
	}
	return false;
}

void solve(string filename) {
	auto lines = split_lines(filename);
	vector<hand> hands {};
	vector<int> value {};
  std::map<hand, int> hand_to_value_map {};
	for (const auto &line : lines) {
		vector<string> l = tokenize<string>(line);
		auto cards = l.at(0);
		hand h(cards.begin(), cards.end());
		hands.push_back(h);
    int v = std::atoi(l.at(1).c_str());
		value.push_back(v);
    hand_to_value_map[h] = v;
	}

	std::sort(hands.begin(), hands.end(), cmp_fn);
	// std::cerr << "Got hand: " << std::endl;
	for (int i = 0; i < hands.size(); i++) {
		// std::cerr << hand_value(hands.at(i)) << " ";
		std::cerr << hands.at(i) << ": " << hand_to_value_map[hands.at(i)] << std::endl;
	}

  int res {0};
  for (int i=0; i<hands.size(); i++) {
    res += hand_to_value_map[hands.at(i)] * ( i +1);
  }
  std::cout << res << std::endl;
}


int main(int argc, char *argv[]) {
	solve(argv[1]);
	return 0;
}
