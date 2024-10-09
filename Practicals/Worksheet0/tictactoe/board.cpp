#include "board.hpp"

#include <iostream>


void TickTacToe::PrintBoard(){
    std::cout << "\n\n\n\n" << std::endl;
    std::cout << "Current Board:\n" << std::endl; 

    
    for (int y = 0; y <3; y++){

        for (int x = 0; x <3; x++){

            std::cout << (this->board->possibleMoves[x][y] == Move::EMPTY ? "   " : this->board->possibleMoves[x][y] == Move::O ? " O " : " X ");


            if (x < 2) {
                std::cout << " | ";
            } else {
                std::cout << std::endl;
            }

        }

        if (y < 2) {
            std::cout << "---------------" << std::endl;
        }
    }


}


Board::Board(){

    for (int y = 0; y <3; y++ ){
        for (int x = 0; x <3; x++ ){

            this->possibleMoves[x][y] = Move::EMPTY;
        }
    }
}






TickTacToe::TickTacToe(){
    this->ResetGame();
}

bool TickTacToe::MakeChoice(){

    int x,y;

    std::cout << "Current Player : " << (this->Turn == Move::X ? "X" : "O") << std::endl;
    std::cout << "Enter your move (row and column): ";
    std::cin >> x >> y;


    if (this->board->possibleMoves[x][y] != Move::EMPTY){
        return false;
    }

    this->board->possibleMoves[x][y] = Turn;

    if (this->Turn == Move::X){
        this->Turn = Move::O;
        return true;
    }

    this->Turn = Move::X;
    return true;
}

void TickTacToe::ResetGame(){

    this->board = new Board();
    this->Turn = Move::X;
}

Move TickTacToe::WinCondition(){

    for (int i = 0; i < 3; i++){
        
        //Checking rows
        if(this->board->possibleMoves[i][0] != Move::EMPTY && (
                this->board->possibleMoves[i][0] == this->board->possibleMoves[i][1] &&
                this->board->possibleMoves[i][1] == this->board->possibleMoves[i][2]
            )
        ) {
            return this->board->possibleMoves[i][0];
        }


        //checking columns
        if(this->board->possibleMoves[0][i] != Move::EMPTY && (
                this->board->possibleMoves[0][i] == this->board->possibleMoves[1][i] &&
                this->board->possibleMoves[1][i] == this->board->possibleMoves[2][i]
            )
        ) {
            return this->board->possibleMoves[0][i];
        }

    }


    //diaganal checks

    //tl-br

    if (this->board->possibleMoves[0][0] != Move::EMPTY && (
            this->board->possibleMoves[0][0] == this->board->possibleMoves[1][1] &&
            this->board->possibleMoves[1][1] == this->board->possibleMoves[2][2]
        )
    ) {
        return this->board->possibleMoves[0][0];
    }

    //tr-bl
    if (this->board->possibleMoves[0][2] != Move::EMPTY && (
        this->board->possibleMoves[0][2] == this->board->possibleMoves[1][1] &&
        this->board->possibleMoves[1][1] == this->board->possibleMoves[2][0]
        )
    ) {
        return this->board->possibleMoves[0][2];
    }

    return Move::EMPTY;

}