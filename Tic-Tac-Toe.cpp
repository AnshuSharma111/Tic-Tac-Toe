#include <iostream>
#include <string>

int main()
{
    std::cout << "Welcome to Tic-Tac-Toe!";
    int choice;

    while (1) {
        std::cout << "\nPlease select Game Mode\n";
        std::cout << "1. 1-Player\n2. 2-Player\n3. Exit\nEnter 1 or 2 or 3 per choice:";

        try {
            std::cin >> choice;

            if (choice == 1) {
                std::cout << "AI MODE\n";
            }
            else if (choice == 2) {
                std::cout << "2 PLAYER MODE\n";
            }
            else if (choice == 3) {
                std::cout << "\nThanks for playing!";
                exit(0);
            }
            else {
                throw;
            }
        }
        catch (...) {
            std::cout << "\nPlease enter 1 or 2 or 3!";
        }
    }
}