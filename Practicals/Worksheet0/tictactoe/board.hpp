#pragma once


enum class Move : char {
    EMPTY = ' ',
    X = 'X',
    O = 'O',

    
};


struct Board {

    Move possibleMoves[3][3];

    Board();

};

class TickTacToe {
public:

    TickTacToe();

    void ResetGame();

    Move WinCondition();

    bool MakeChoice();

    void PrintBoard();

private:
    Move Turn;

    Board* board;


};