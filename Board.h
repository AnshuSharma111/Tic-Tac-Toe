#include <vector>

class Board {
private:
	static const int BOARD_SIZE = 9; // size of the board
	int turn; // 0 indicates player 1 and 1 indicates player 2
	std::vector<char> board; // the actual board object

	// Internal Board Functions
	bool isLeaf(); // check whether board is full or not
	int evaluate(); // 0 means draw, 1 means victory for player 1 and -1 victory for player 2

	// Internal AI functions
	std::vector<std::vector<char>> children(std::vector<char> current); // generate all children of current state
	std::vector<char> bestChild(std::vector<char> current, int levelType); // get the best child of the current board levelType is -1 for min and 1 for max
public:
	// Constructor & Destructor
	Board();

	// Board Functions
	void render(); // print the current board
	void mark(int square); // mark square with character 'O' or 'X'

	// AI functions
	int nextMove(); // the next move the AI will take
};