//
//  Board.h
//  Lab 9
//
//  Created by Kari Freckleton on 11/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef Lab_9_Board_h
#define Lab_9_Board_h

#include <iostream>
using namespace std;

static const int BOARD_SIZE = 9;

class Board{
    friend ostream & operator<<(ostream & out, Board b);
public:
    Board();
    Board(int savedArray[BOARD_SIZE][BOARD_SIZE], int savedMoveArray[BOARD_SIZE][BOARD_SIZE]);
    void display();
    void output(ostream & out);
    bool turn(int row, int column, int value);
    bool boardFull();
    bool boardSolved();
    int getValue(int row, int column);
private:
    int boardArray[BOARD_SIZE][BOARD_SIZE];
    int canMoveArray[BOARD_SIZE][BOARD_SIZE];
};

#endif
