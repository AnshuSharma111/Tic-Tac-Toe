#include "Engine.h"

std::pair<bool, endState> Engine::isLeaf(std::vector<char>& board) {
	endState state = evaluate(board);

	if (state == endState::P1Win || state == endState::P2Win) return { true, state };

	bool isFull = true;
	for (int i = 1; i <= BOARD_SIZE; i++) {
		if (board[i - 1] == '.') {
			isFull = false; 
			break;
		}
	}

	if (isFull) return { true, endState::Draw };
	return { false, state };
}

endState Engine::evaluate(std::vector<char>& board) {
	std::vector<std::vector<int>> winning_combs = {
		{0, 1, 2}, // rows
		{3, 4, 5},
		{6, 7, 8},
		{0, 3, 6}, // columns
		{1, 4, 7},
		{2, 5, 8},
		{0, 4, 8}, // diagonals
		{2, 4, 6}
	};

	for (const auto& comb : winning_combs) {
		if (board[comb[0]] == 'O' && board[comb[1]] == 'O' && board[comb[2]] == 'O') return endState::P1Win;
		if (board[comb[0]] == 'X' && board[comb[1]] == 'X' && board[comb[2]] == 'X') return endState::P2Win;
	}

	return endState::Draw;
}

std::pair<int, endState> Engine::bestChild(std::vector<char>& board, nodeType level, Player turn) {
	// leaf node
	std::pair<bool, endState> state = isLeaf(board);
	if (state.first == true) return { -1, state.second };

	// next level parameters
	nodeType nextLevel = (level == nodeType::MIN) ? nodeType::MAX : nodeType::MIN;
	Player nextTurn = (turn == Player::P1) ? Player::P2 : Player::P1;

	// if we found a DRAW condition or a LOSE condition
	int drawMove = -1;
	int loseMove = -1;

	for (int i = 1; i <= BOARD_SIZE; i++) {
		if (board[i - 1] == '.') {
			board[i - 1] = (turn == Player::P1) ? 'O' : 'X';
			auto res = bestChild(board, nextLevel, nextTurn);
			board[i - 1] = '.';

			endState eval = res.second;

			if (level == nodeType::MIN && eval == endState::P1Win) return { i, endState::P1Win };
			if (level == nodeType::MAX && eval == endState::P2Win) return { i, endState::P2Win };

			if (drawMove == -1 && eval == endState::Draw) drawMove = i;
			else if (loseMove == -1 && level == nodeType::MIN && eval == endState::P2Win) loseMove = i;
			else if (loseMove == -1 && level == nodeType::MAX && eval == endState::P1Win) loseMove = i;
		}
	}

	// return DRAW con if available
	if (drawMove != -1) return { drawMove, endState::Draw };
	// cannot WIN or DRAW from here :<
	return { loseMove, (level == nodeType::MIN) ? endState::P2Win : endState::P1Win };
}

int Engine::nextMove(Board& boardObj) {
	std::vector<char> board = boardObj.getBoard();
	std::pair<int, endState> move = bestChild(board, nodeType::MAX, Player::P2);
	return move.first;
}

std::pair<bool, endState> Engine::isFinished(const Board& boardObj) {
	std::vector<char> board = boardObj.getBoard();
	return isLeaf(board);
}