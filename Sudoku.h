#ifndef Sudoku_h
#define Sudoku_h

#include "Board.h"
#include <stack>

class Sudoku{
public:
    Sudoku();
    void gamePlay(Board & b);
    void saveGame(Board & b);
    void undoMove(Board & b);
    void normalTurn(Board & b);
    void getCommand();
private:
    stack <int> moves;
    char command;
    int row;
    int column;
    int value;
};

#endif
