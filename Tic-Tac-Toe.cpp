#include <iostream>
#include <string>
#include <limits>

#include "Board.h"

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
                std::cout << "Thanks for plating!\n";
                exit(0);
            }
            else {
                Board board;
                board.render();
            }
        }
        else {
            std::cout << "Please enter 1 or 2 or 3 only!\n";
        }
    }
}