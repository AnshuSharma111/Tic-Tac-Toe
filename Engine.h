#pragma once
#include <vector>
#include "Board.h"

enum class endState {
	P1Win,
	P2Win,
	Draw
};

enum class nodeType {
	MIN,
	MAX
};

class Engine {
private:
	static const int BOARD_SIZE = 9;

	// Internal Functions
	bool isLeaf(const std::vector<char>& board); // check whether board is a leaf node or not
	endState evaluate(const std::vector<char>& board); // P1Win or P2Win or Draw

	std::vector<std::vector<char>> children(const std::vector<char>& board, Player turn); // generate all children of current state
	std::pair<endState, std::vector<char>> bestChild(const std::vector<char>& board, nodeType level, Player turn); // get best child possible
public:
	// AI functions
	int nextMove(const Board& boardObj); // the next move the AI should take

	// Game Utility
	bool isFinished(const Board& boardObj); // is the game complete?
};