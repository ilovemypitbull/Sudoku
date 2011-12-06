#include <iostream>
#include <fstream>
#include "Sudoku.h"
Sudoku::Sudoku(){
    
    char loadFromFile;
    cout << "Would you like to load a game from file?(y/n)";
    cin >> loadFromFile;
    if (loadFromFile == 'y') {
        int tempArray[BOARD_SIZE][BOARD_SIZE];
        int tempMovesArray [BOARD_SIZE][BOARD_SIZE];
        ifstream infile;
        infile.open("gamefile.txt");
        if (infile.is_open()) {
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    infile >> tempArray[i][j];
                }
            }
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    infile >> tempMovesArray[i][j];
                }
            }
            infile.close();
            Board savedBoard(tempArray, tempMovesArray);
            gamePlay(savedBoard);
        }
        else{
            cout << "Couldn't open file. Starting new game instead." << endl;
            Board newBoard;
            gamePlay(newBoard);
        }
    }
    else{
        Board newBoard;
        gamePlay(newBoard);
    }
    
}

void Sudoku::gamePlay(Board & b){
    
    
    b.display();
    
    if (!b.boardFull()) {
        getCommand();
    }
    

    while (command != 'q' && !b.boardSolved()) {
        
        if (command == 'u') {
            undoMove(b);
            b.display();
        }
        else {
            normalTurn(b);
            b.display();
        }
        
        if (!b.boardSolved()) {
            if (b.boardFull())
                cout << "The board is full but not solved." << endl;
            getCommand();
        }
        
        
    }

    if (b.boardSolved()) {
        cout << "Congratulations! You solved the board." << endl;
    }
    

    

    
    if (command == 'q') {
        char answer;
        cout << "Save game?(y/n)" << endl;
        cin >> answer;
        if (answer == 'y') {
            saveGame(b);
        }
    }
}

void Sudoku::saveGame(Board & b)
{
    ofstream outfile;
    outfile.open("gamefile.txt");
    if (!outfile.is_open()) {
        cout << "Game cout not be saved" << endl;
    }
    outfile << b;
    outfile.close();
}

void Sudoku::undoMove(Board & b)
{
    int row;
    int column;
    int value;
    if (!moves.empty()) {
        row = moves.top();
        moves.pop();
        column = moves.top();
        moves.pop();
        value = moves.top();
        moves.pop(); 
        b.turn(row, column, value);
    }
    else
        cout << "No moves to undo" << endl;
}

void Sudoku::normalTurn(Board & b){
    cout << "Enter a row (1-9)" << endl;
    cin >> row;
    row--;
    cout << "Enter a column (1-9)" << endl;
    cin >> column;
    column--;
    moves.push(b.getValue(row, column));
    moves.push(column);
    moves.push(row);
    cout << "Enter a value (1-9)" << endl;
    cin >> value;
    b.turn(row, column, value);
}

void Sudoku::getCommand(){
    cout << "What would you like to do?" << endl;
    cout << "Make a move(m)" << endl;
    if (!moves.empty())
        cout << "Undo last move(u)" << endl;
    cout << "Quit(q)" << endl;
    cin >> command;
}