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

std::pair<int,int> Engine::minimaxChild(std::vector<char>& board, Player turn) {
	// leaf node
	std::pair<bool, endState> state = isLeaf(board);
	if (state.first == true) {
		int score = 0;
		if (state.second == endState::P1Win) score = 100;
		if (state.second == endState::P2Win) score = -100;
		return { -1, score };
	}

	// next level turn
	Player nextTurn = (turn == Player::P1) ? Player::P2 : Player::P1;
	std::pair<int,int> move = { -1, -1 };

	for (int i = 1; i <= BOARD_SIZE; i++) {
		if (board[i - 1] == '.') {
			board[i - 1] = (turn == Player::P1) ? 'O' : 'X';
			auto res = minimaxChild(board, nextTurn);
			board[i - 1] = '.';

			int score = res.second;

			// decrease score for depth
			if (score > 0) score -= 1;
			else if (score < 0) score += 1;

			if (turn == Player::P1) { // MAX node
				if (move.first == -1 || move.second < score) {
					move.first = i;
					move.second = score;
				}
			}
			else { // MIN node
				if (move.first == -1 || move.second > score) {
					move.first = i;
					move.second = score;
				}
			}
		}
	}

	return move;
}

int Engine::nextMove(Board& boardObj) {
	std::vector<char> board = boardObj.getBoard();
	std::pair<int, int> result = minimaxChild(board, Player::P2);
	return result.first;
}

std::pair<bool, endState> Engine::isFinished(const Board& boardObj) {
	std::vector<char> board = boardObj.getBoard();
	return isLeaf(board);
}