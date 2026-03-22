#pragma once
#include <vector>
#include <limits>
#include "Board.h"

enum class state {
	Ongoing,
	P1Win,
	P2Win,
	Draw
};

class Engine {
private:
	static const int BOARD_SIZE = 9;

	// Internal Functions
	state evaluate(std::vector<char>& board); // P1Win or P2Win or Draw or Ongoing
	std::pair<int,int> minimaxChild(std::vector<char>& board, Player turn, int alpha, int beta); // get best move possible
public:
	// AI functions
	int nextMove(Board& boardObj); // the next move the AI should take

	// Game Utility
	state gameState(const Board& boardObj); // What is the current state of the game?
};