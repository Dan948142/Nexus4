#include "board.h"
#include <iostream>
using namespace std;

Board::Board(){
    bitboards[0] = bitboards[1] = 0;
    moveCount = 0;

    for(int i=0;i<7;i++){
        height[i] = i*7;        // points at the bottom row of each coloumn
    }
    // we have kept a buffer index for each row
}

bool Board::isValidMove(int col) const{
    return height[col] < (col*7+6);
}

void Board::makeMove(int col){
    uint64_t move = 1ULL<<height[col]++;
    bitboards[0] ^= move;
    swap(bitboards[0], bitboards[1]);
    moveCount++;
    // current player is always 0
}

bool Board::checkWin(uint64_t bitboard) const{
    int directions[] = {1,7,6,8}; // vertical, horizontal, diagonal down, diagonal up

    for(auto dir:directions){
        uint64_t m = bitboard & (bitboard >> dir);
        if(m & (m>> (2*dir))) return true; 
    }
    return false;
}

bool Board::isFull() const{
    return moveCount == 42;
}

void Board::printBoard() const{
    uint64_t p1 = (moveCount % 2 == 0) ? bitboards[0] : bitboards[1];
    uint64_t p2 = (moveCount % 2 == 0) ? bitboards[1] : bitboards[0];

    cout << "\n";
    for(int r=5;r>=0;r--){
        for(int c=0;c<7;c++) {
            uint64_t mask = 1ULL << (c * 7 + r);
            if (p1 & mask) cout<<"| X ";
            else if (p2 & mask) cout<<"| O ";
            else cout<<"|   ";
        }
        cout<<"|\n";
    }
    cout<<"-----------------------------\n  0   1   2   3   4   5   6\n";
}