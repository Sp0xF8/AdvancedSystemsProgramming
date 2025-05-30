#include "board.hpp"

#include <iostream>

int main(){

    TickTacToe* runningGame = new TickTacToe();


    while(true) {

        std::cout << "Welcome to the TickTacToe Game!" << std::endl;

        while(true) {

            runningGame->PrintBoard();

            runningGame->MakeChoice();

            Move Winner = runningGame->WinCondition();

            if (Winner != Move::EMPTY){
                runningGame->PrintBoard();
                std::cout << "The winner is " << (Winner == Move::O ? "O" : "X") << std::endl;
                break;
            }
        }

        std::cout << "Thanks for playing! Another round? (y/n)" << std::endl;

        char input;

        std::cin >> input;

        if (input != 'y' || input != 'Y') {
            break;
        }



    }



    return 1;
}