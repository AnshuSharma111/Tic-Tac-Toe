#pragma once
#include <vector>

// Players
enum class Player {
	P1,
	P2
};

class Board {
private:
	static const int BOARD_SIZE = 9; // size of the board
	Player turn; // either P1 or P2
	std::vector<char> board; // the actual board object

public:
	// Constructor & Destructor
	Board();

	// Board Functions
	void render(); // print the current board
	void mark(int square); // mark square with character 'O' or 'X'

	// getters
	Player getTurn() const; // get whoose turn it is
	std::vector<char> getBoard() const; // get the board
};