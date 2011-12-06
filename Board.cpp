#include <iostream>
#include "Board.h"
#include <time.h>
#include <vector>


Board::Board(){
    srand ( static_cast<int>(time(NULL)) );
    for (int i = 0; i < BOARD_SIZE; i++) { // intializes board to solvable solution I developed
        for (int j = 0; j < BOARD_SIZE; j++) {
            boardArray[i][j] = j + ((i/3) + 3* (i % 3)) + 1;
            if (boardArray[i][j] > 9) {
                boardArray[i][j] = boardArray[i][j]-9;
            }
        }
    }
    
     
    // swap individual numbers
     
    int numSwaps = 10 + rand() % 5;
    
    while (numSwaps > 0) {
        int num1 = rand() % 9 + 1;
        int num2 = rand() % 9 + 1;
        if (num1 != num2) {
            numSwaps--;
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (boardArray[i][j] == num1) {
                        boardArray[i][j] = num2;
                    }
                    else if (boardArray[i][j] == num2){
                        boardArray[i][j] = num1;
                    }
                    else
                        continue;
                }
            }
        }
    }
    
    
    // swap rows
    
    int rowSwaps = 10 + rand() % 5;
     
    while (rowSwaps > 0) {
        int row1Pos = rand() % 9 + 1;
        int row2Pos = rand() % 9 + 1;
        
        if (((row1Pos / 3) == (row2Pos / 3)) && (row1Pos != row2Pos)){
            int row1[BOARD_SIZE];
            int row2[BOARD_SIZE];
            
            for (int i = 0; i < BOARD_SIZE; i++) {
                row1[i] = boardArray[row1Pos][i];
                row2[i] = boardArray[row2Pos][i];
            }
            rowSwaps--;
            for (int i = 0; i < BOARD_SIZE; i++) {
                boardArray[row1Pos][i] = row2[i];
                boardArray[row2Pos][i] = row1[i];
            }
        }
      
    }
     
    
    // swap columns
    
    int colSwaps = 10 + rand() % 5;
    
    while (colSwaps > 0) {
        int col1Pos = rand() % 9 + 1;
        int col2Pos = rand() % 9 + 1;
        
        if (((col1Pos / 3) == (col2Pos / 3)) && (col1Pos != col2Pos)){
            int col1[BOARD_SIZE];
            int col2[BOARD_SIZE];
            
            for (int i = 0; i < BOARD_SIZE; i++) {
                col1[i] = boardArray[i][col1Pos];
                col2[i] = boardArray[i][col2Pos];
            }
            colSwaps--;
            for (int i = 0; i < BOARD_SIZE; i++) {
                boardArray[i][col1Pos] = col2[i];
                boardArray[i][col2Pos] = col1[i];
            }
        }
        
    }
    
    for (int i = 0; i < BOARD_SIZE; i++) { // intializes board of changable cells to be not changable 
        for (int j = 0; j < BOARD_SIZE; j++) {
            canMoveArray[i][j] = 0;
        }
    }
    
    int takeAway = 30 + rand() % 9; // change to make easier or harder
    while (takeAway > 0) {
        int randomX = rand() % 9;
        int randomY = rand() % 9;
        if (boardArray[randomX][randomY] != 0) {
            boardArray[randomX][randomY] = 0;
            canMoveArray[randomX][randomY] = 1; // turns on chagability for that cell
            takeAway--;
        }
    }
    
}

Board::Board(int savedArray[BOARD_SIZE][BOARD_SIZE], int savedMoveArray[BOARD_SIZE][BOARD_SIZE]){
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            boardArray[i][j]= savedArray[i][j];
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            canMoveArray[i][j] = savedMoveArray[i][j];
        }
    }
}

void Board::display(){
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (j > 0 && j % 3 == 0) {
                cout << "| " ;
            }
            if (i > 0 && i % 3 == 0 && j == 0) {
                cout << "----------------------" << endl;
            }
            if (boardArray[i][j] == 0) 
                cout << "_ ";
            else
                cout << boardArray[i][j] << " ";
        }
        cout << endl;
    }
}

void Board::output(ostream & out){
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            out << boardArray[i][j] << " ";
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            out << canMoveArray[i][j] << " ";
        }
    }
}


bool Board::turn(int row, int column, int value){
    if (canMoveArray[row][column] == 0) {
        cout << "That position on the board can't be changed" << endl;
        return false;
    }
    if (value < 0 || value > 9) {
        cout << "Invalid value" << endl;
        return false;
    }
    if (row < 0 || row > 8) {
        cout << "Invalid row" << endl;
        return false;
    }
    if (column < 0 || column > 8) {
        cout << "Invalid column" << endl;
        return false;
    }
    else {
        boardArray[row][column] = value;
        return true;
    }
}

bool Board::boardFull(){
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j <BOARD_SIZE; j++) {
            if (boardArray[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

bool Board::boardSolved(){
  if (!boardFull()) {
       return false;
}
    bool kFound = false;
    
    // testing for all nine digits in each row
    for (int k = 1; k < 10; k++) {
        
        for (int i = 0; i < BOARD_SIZE; i++) {
            kFound = false;
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (boardArray[i][j] == k) {
                    kFound = true;
                }
            }
            if (!kFound){
                return false;
            }
        }
    }
    
     // testing for all nine digits in each column
    
    for (int k = 1; k < 10; k++) {
        
        for (int j = 0; j < BOARD_SIZE; j++) {
            kFound = false;
            for (int i = 0; i < BOARD_SIZE; i++) {
                if (boardArray[i][j] == k) {
                    kFound = true;
                }
            }
            if (!kFound){
                return false;
            }
        }
    }
    
    // testing for all nine digits in each cell
    
    int i;
    int j;
    for (int k = 1; k < 10; k++) {
    
    // cell one
        kFound = false;
    
        for (i = 0; i < 3; i++){
            for (j = 0; j < 3; j++) {
                if (boardArray[i][j] == k) {
                    kFound = true;
                }
            }
        }
        
        if (!kFound){
            return false;
        }
        
    // cell two
        kFound = false;
        
        for (i = 0; i < 3; i++){
            for (j = 3; j < 6; j++) {
                if (boardArray[i][j] == k) {
                    kFound = true;
                }
            }
        }
        if (!kFound){
            return false;
        }
        
    // cell three
        kFound = false;
        
        for (i = 0; i < 3; i++){
            for (j = 6; j < 9; j++) {
                if (boardArray[i][j] == k) {
                    kFound = true;
                }
            }
        }
        if (!kFound){
            return false;
        }    
        // cell four
        kFound = false;
        
        for (i = 3; i < 6; i++){
            for (j = 0; j < 3; j++) {
                if (boardArray[i][j] == k) {
                    kFound = true;
                }
            }
        }
        
        if (!kFound){
            return false;
        }
        
        // cell five
        kFound = false;
        
        for (i = 3; i < 6; i++){
            for (j = 3; j < 6; j++) {
                if (boardArray[i][j] == k) {
                    kFound = true;
                }
            }
        }
        if (!kFound){
            return false;
        }
        
        // cell six
        kFound = false;
        
        for (i = 3; i < 6; i++){
            for (j = 6; j < 9; j++) {
                if (boardArray[i][j] == k) {
                    kFound = true;
                }
            }
        }
        if (!kFound){
            return false;
        } 
        // cell seven
        kFound = false;
        
        for (i = 6; i < 9; i++){
            for (j = 0; j < 3; j++) {
                if (boardArray[i][j] == k) {
                    kFound = true;
                }
            }
        }
        
        if (!kFound){
            return false;
        }
        
        // cell eight
        kFound = false;
        
        for (i = 6; i < 9; i++){
            for (j = 3; j < 6; j++) {
                if (boardArray[i][j] == k) {
                    kFound = true;
                }
            }
        }
        if (!kFound){
            return false;
        }
        
        // cell nine
        kFound = false;
        
        for (i = 6; i < 9; i++){
            for (j = 6; j < 9; j++) {
                if (boardArray[i][j] == k) {
                    kFound = true;
                }
            }
        }
        if (!kFound){
            return false;
        } 
    }

    return true;
}

int Board::getValue(int row, int column){
    return boardArray[row][column];
}

ostream &  operator<<(ostream & out, Board b){
    b.output(out);
    return out;
}