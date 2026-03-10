#include "Board.h"
#include <iostream>

Board::Board() {
	// player 1 starts first
	turn = Player::P1;

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

	if (turn == Player::P1) {
		board[square - 1] = 'O'; // Player 1 move
		turn = Player::P2;
	}
	else {
		board[square - 1] = 'X'; // Player 2 move
		turn = Player::P1;
	}
}

Player Board::getTurn() const {
	return turn;
}

std::vector<char> Board::getBoard() const {
	return board;
}