#include <iostream>
#include <vector>
using namespace std;

// The Board State
class Board {
public:
    uint64_t bitboards[2];
    // bitboard[0] is the current player and bitboard[1] is the opponent
    int height[7];  // tracks lowest empty row index
    int moveCount;

    Board();
    bool isValidMove(int col) const;
    void makeMove(int col); 
    bool checkWin(uint64_t bitboard) const;
    bool isFull() const;
    void printBoard() const;    
};
