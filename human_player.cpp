#include "human_player.h"
#include <iostream>
#include <limits>

int HumanPlayer::getMove(const Board& board) {
    int col;
    while (true) {
        cout<<name<<" (" << piece << "), enter column (0-6): ";
        cin>>col;

        if(cin.fail()){
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout<<"Invalid input. Please enter a number.\n";
        } 
        else if(board.isValidMove(col)){
            return col;
        } 
        else{
            cout << "Invalid move. Column is full or out of bounds.\n";
        }
    }
}