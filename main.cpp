#include <iostream>
#include "Sudoku.h"
#include <fstream>

using namespace std;

int main ()
{
    char playAgain = 'y';
    
    while (playAgain == 'y') {
        Sudoku s1;
        cout << "Would you like to play again?(y/n)" << endl;
        cin >> playAgain;
    }
    
    return 0;
}

