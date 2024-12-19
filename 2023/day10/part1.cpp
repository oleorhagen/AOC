#include "../utils.hpp"
#include <cassert>
#include <queue>

using std::vector;

using map = vector<vector<char>>;

enum class Direction {North, South, East, West};

using Pos = std::pair<int, int>;

char traverse(Direction dir, map m, Pos pos) {
  try {
    switch (dir) {
    case Direction::North:
      return m[pos.first+1][pos.second];
    case Direction::South:
      return m[pos.first-1][pos.second];
    case Direction::East:
      return m[pos.first][pos.second+1];
    case Direction::West:
      return m[pos.first][pos.second-1];
    }
  } catch(...) {
    return '.';
  }
  assert( false );
}

vector<char> adjacents(map m, Pos p) {
  return {
    traverse(Direction::North, m,p),
    traverse(Direction::South, m,p),
    traverse(Direction::East, m,p),
    traverse(Direction::West, m,p),
  };
}

class Node {
 public:
  int depth;
  vector<string> positive;
  vector<string> negative;
};

vector<Pos> neighbours4(Pos p) {
  return {
    {p.first - 1, p.second},
    {p.first, p.second - 1},
    {p.first + 1, p.second},
    {p.first, p.second + 1},
  };
}

std::map<string, Node> ns {
  {"|",
   Node{0,
        {"7", "|", "F"},
        {"L", "|", "J"},
   },
  },
  {"7",
   Node{0,
      {"-", "L", "F"},
      {"|", "J", "L"}},
  },
  {"J",
   Node{0,
        {"7", "|", "F"},
        {"L", "-", "F"}},
  },
  {"-",
   Node{0,
        {"-", "L", "F"},
        {"-", "J", "7"}},
  },
  {
    "F",
    Node{0,
         {"J", "-", "7"},
         {"L", "-", "J"}},
  },
  {
    "L",
    Node{0,
         {"F", "|", "7"},
         {"L", "|", "J"}},
  },
};



bool canVisit(Pos p) {
  // TODO - Implement
  return true;
}

void find_main_loop(map m, std::pair<int,int> pos) {

  // Create a visited map
  vector<vector<bool>> visited(m.size(), vector<bool>(m.size(), false));

  // Do a BFS on the map, starting from pos
  visited[pos.first][pos.second] = true;

  // For each pos, there are only 4 directions we can go!
  // std::queue<Pos> neighbours {{ pos }};

  std::queue<Pos> q {{pos}};

  while (not q.empty()) {
    Pos cur {q.front()};
    // int { x, y } = cur;
    int x = cur.first;
    int y = cur.second;

    std::cout << m[x][y] << " ";

    q.pop();

    // Go to the adjacent cells
    vector<Pos> neighbours = neighbours4(cur);
    for( const auto neighbour : neighbours) {
      if (not visited[neighbour.first][neighbour.second] and canVisit(neighbour)) {
        q.push(neighbour);
        visited[neighbour.first][neighbour.second] = true;
      }
    }

  }


  return;
}

void solve(string filename) {
  auto lines = split_lines(filename);

  map matrix = create_matrix(lines);

  // Build graph

  /* For each tile, try and find the main loop */
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[0].size(); j++) {
			std::cerr << matrix[i][j];
		}
		std::cerr << std::endl;
	}

  find_main_loop(matrix, {0,0});

  return;
}


int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Requires a named file as input!" << std::endl;
    return 0;
  }
	solve(argv[1]);
	return 0;
}
