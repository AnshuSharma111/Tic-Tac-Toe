#pragma once
#include <vector>
#include "Board.h"

enum class endState {
	P1Win,
	P2Win,
	Draw
};

class Engine {
private:
	static const int BOARD_SIZE = 9;

	// Internal Functions
	std::pair<bool, endState>  isLeaf(std::vector<char>& board); // check whether board is a leaf node or not
	endState evaluate(std::vector<char>& board); // P1Win or P2Win or Draw

	std::pair<int,int> minimaxChild(std::vector<char>& board, Player turn); // get best move possible
public:
	// AI functions
	int nextMove(Board& boardObj); // the next move the AI should take

	// Game Utility
	std::pair<bool, endState> isFinished(const Board& boardObj); // is the game complete? And if yes, who won?
};