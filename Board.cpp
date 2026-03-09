#include "Board.h"
#include <iostream>

Board::Board() {
	// player 1 starts first
	turn = 0;

	// '.' denotes an empty slot and 'O' and 'X' denote their symbols
	board.resize(BOARD_SIZE, '.');
}

void Board::render() {
	std::cout << std::endl;

	for (int i = 1; i <= BOARD_SIZE; i++) {
		std::cout << " " << board[i - 1] << " ";

		if (i % 3 == 0 && i != 9) {
			std::cout << '\n';
			std::cout << "---+---+---\n";
		}
		else if (i != 9) {
			std::cout << "|";
		}
	}

	std::cout << std::endl;
}

void Board::mark(int square) {
	if (square > BOARD_SIZE || square <= 0 || board[square - 1] != '.') {
		std::cout << "Illegal Move!\n";
		return;
	}

	if (turn == 0) {
		board[square - 1] = 'O'; // Player 1 move
		turn = 1;
	}
	else {
		board[square - 1] = 'X'; // Player 2 move
		turn = 0;
	}
}

int Board::evaluate() {
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
		if (board[comb[0]] == 'O' && board[comb[1]] == 'O' && board[comb[2]] == 'O') return 1;
		if (board[comb[0]] == 'X' && board[comb[1]] == 'X' && board[comb[2]] == 'X') return -1;
	}

	return 0;
}

bool Board::isLeaf() {
	for (int i = 1; i <= BOARD_SIZE; i++) {
		if (board[i - 1] == '.') return false;
	}
	return true;
}

std::vector<std::vector<char>> Board::children(std::vector<char> current) {
	// board is full, no children possible
	if (isLeaf()) {
		return {};
	}

	// generate children
	std::vector<std::vector<char>> childs;
	for (int i = 1; i <= BOARD_SIZE; i++) {
		if (board[i - 1] == '.') {
			std::vector<char> child;
			std::copy(current.begin(), current.end(), child.begin());
			child[i - 1] = 'X';
			childs.push_back(child);
		}
	}

	return childs;
}

//int Board::nextMove() {
//	std::vector<std::vector<char>> next = children(board);
//}
//
//std::vector<char> Board::bestChild(std::vector<char> current, int levelType) {
//	// generate next level
//	std::vector<std::vector<char>> next = children(board);
//
//	// if no children, means we have a leaf node
//	if (next.empty()) {
//		return current;
//	}
//}