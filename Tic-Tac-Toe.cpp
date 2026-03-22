#include <iostream>
#include <string>
#include <limits>

#include "Board.h"
#include "Engine.h"

void engineGame() {
    Engine engine;
    Board board;
    int markSq;

    std::cout << "Let's start the game!\n";
    board.render();

    while (1) {
        state current = engine.gameState(board);
        if (current != state::Ongoing) {
            std::cout << "Game Finished!";

            if (current == state::P1Win) std::cout << "You Win!\n";
            else if (current == state::P2Win) std::cout << "The Engine Wins!\n";
            else std::cout << "The game ended in a Draw!\n";

            break;
        }

        if (board.getTurn() == Player::P1) {
            std::cout << "Please enter the cell you want to mark (1 - 9): ";
            std::cin >> markSq;

            board.mark(markSq);
        }
        else if (board.getTurn() == Player::P2) {
            std::cout << "Engine Turn: ";
            int next = engine.nextMove(board);
            std::cout << next;
            board.mark(next);
        }

        board.render();
    }
}

void twoPlayerGame() {
    Board board;
    Engine engine;
    int markSq;

    std::cout << "Let's start the game!\n";
    board.render();

    while (1) {
        state current = engine.gameState(board);
        if (current != state::Ongoing) {
            std::cout << "Game Finished!";

            if (current == state::P1Win) std::cout << "Player 1 Wins!\n";
            else if (current == state::P2Win) std::cout << "Player 2 Wins!\n";
            else std::cout << "The game ended in a Draw!\n";

            break;
        }
        if (board.getTurn() == Player::P1) {
            std::cout << "Player 1's turn (O): ";
            std::cin >> markSq;

            board.mark(markSq);
        }
        else if (board.getTurn() == Player::P2) {
            std::cout << "Player 2's turn (X): ";
            std::cin >> markSq;

            board.mark(markSq);
        }

        board.render();
    }
}

int main()
{
    std::cout << "Welcome to Tic-Tac-Toe!";
    std::string choice;

    while (1) {
        std::cout << "\nPlease select Game Mode\n";
        std::cout << "1. 1-Player\n2. 2-Player\n3. Exit\nEnter 1 or 2 or 3 per choice:";

        std::getline(std::cin, choice);
        if (choice == "1" || choice == "2" || choice == "3") {
            if (choice == "3") {
                std::cout << "Thanks for Playing!\n";
                exit(0);
            }
            else if (choice == "1") {
                engineGame();
            }
            else {
                twoPlayerGame();
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            std::cout << "Please enter 1 or 2 or 3 only!\n";
        }
    }
}