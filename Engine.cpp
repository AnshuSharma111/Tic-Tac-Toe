#include "Engine.h"

bool Engine::isLeaf(const std::vector<char>& board) {
	for (int i = 1; i <= BOARD_SIZE; i++) {
		if (board[i - 1] == '.') return false;
	}
	return true;
}

endState Engine::evaluate(const std::vector<char>& board) {
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

std::vector<std::vector<char>> Engine::children(const std::vector<char>& board, Player turn) {
	// board is full, no children possible
	if (isLeaf(board)) {
		return {};
	}

	// generate children
	std::vector<std::vector<char>> childs;
	for (int i = 1; i <= BOARD_SIZE; i++) {
		if (board[i - 1] == '.') {
			std::vector<char> child(9);
			std::copy(board.begin(), board.end(), child.begin());
			child[i - 1] = (turn == Player::P1) ? 'O' : 'X';
			childs.push_back(child);
		}
	}

	return childs;
}

std::pair<endState, std::vector<char>> Engine::bestChild(const std::vector<char>& board, nodeType level, Player turn) {
	// Generate All Children
	std::vector<std::vector<char>> next = children(board, turn);

	// If this is a win state or a leaf state
	if (evaluate(board) != endState::Draw || next.empty()) {
		return { evaluate(board), board };
	}

	// alternate between MIN and MAX levels and turns
	nodeType nextLevel = (level == nodeType::MIN) ? nodeType::MAX : nodeType::MIN;
	Player nextTurn = (turn == Player::P1) ? Player::P2 : Player::P1;

	std::vector<std::pair<endState, std::vector<char>>> grandchildren;

	for (auto const& child : next) {
		std::pair<endState, std::vector<char>> bestGrandchild = bestChild(child, nextLevel, nextTurn);

		if (bestGrandchild.first == endState::P1Win && level == nodeType::MIN) return { endState::P1Win, child };
		if (bestGrandchild.first == endState::P2Win && level == nodeType::MAX) return { endState::P2Win, child };

		grandchildren.push_back({bestGrandchild.first, child});
	}

	// we did not get a winning position, lets try for draw
	for (auto const& grandchild : grandchildren) {
		if (grandchild.first == endState::Draw) return grandchild;
	}

	// not even a draw is possible
	return grandchildren[0];
}

int Engine::nextMove(const Board& boardObj) {
	std::vector<char> board = boardObj.getBoard();
	Player turn = boardObj.getTurn();

	std::pair<endState, std::vector<char>> bestMove = bestChild(board, nodeType::MAX, turn);

	for (int i = 1; i <= BOARD_SIZE; i++) {
		if (board[i - 1] != bestMove.second[i - 1]) return i;
	}

	return -1;
}

bool Engine::isFinished(const Board& boardObj) {
	// is full
	bool isFull = true;
	std::vector<char> board = boardObj.getBoard();
	for (int i = 1; i <= BOARD_SIZE; i++) {
		if (board[i - 1] == '.') {
			isFull = false;
			break;
		}
	}
	if (isFull) return true;

	// is Won
	endState boardState = evaluate(boardObj.getBoard());
	bool isComplete = (boardState == endState::P1Win || boardState == endState::P2Win) ? true : false;

	return isComplete;
}