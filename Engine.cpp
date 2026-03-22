#include "Engine.h"

state Engine::evaluate(std::vector<char>& board) {
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
		if (board[comb[0]] == 'O' && board[comb[1]] == 'O' && board[comb[2]] == 'O') return state::P1Win;
		if (board[comb[0]] == 'X' && board[comb[1]] == 'X' && board[comb[2]] == 'X') return state::P2Win;
	}

	for (int i = 1; i <= BOARD_SIZE; i++) {
		if (board[i - 1] == '.') return state::Ongoing;
	}

	return state::Draw;
}

std::pair<int,int> Engine::minimaxChild(std::vector<char>& board, Player turn, int alpha, int beta) {
	// leaf node
	state boardState = evaluate(board);
	if (boardState != state::Ongoing) {
		int score = 0;
		if (boardState == state::P1Win) score = 100;
		if (boardState == state::P2Win) score = -100;
		return { -1, score };
	}

	// who will move next?
	Player nextTurn = (turn == Player::P1) ? Player::P2 : Player::P1;
	// current char
	char cur = (turn == Player::P1) ? 'O' : 'X';

	// result storing variable
	std::pair<int,int> move = { -1, -1 };

	for (int i = 1; i <= BOARD_SIZE; i++) {
		if (board[i - 1] == '.') {
			if (alpha >= beta) break;

			board[i - 1] = cur;
			auto res = minimaxChild(board, nextTurn, alpha, beta);
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

				alpha = std::max(alpha, score);
			}
			else { // MIN node
				if (move.first == -1 || move.second > score) {
					move.first = i;
					move.second = score;
				}

				beta = std::min(beta, score);
			}
		}
	}

	return move;
}

int Engine::nextMove(Board& boardObj) {
	std::vector<char> board = boardObj.getBoard();
	std::pair<int, int> result = minimaxChild(board, Player::P2, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
	return result.first;
}

state Engine::gameState(const Board& boardObj) {
	std::vector<char> board = boardObj.getBoard();
	state boardState = evaluate(board);
	return boardState;
}