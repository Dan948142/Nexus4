#include <string>
#include "board.h"

class Player {
protected:
    string name;
    char piece; // Mostly kept just so we can print their name and piece in the terminal
public:
    Player(string n, char p) : name(n), piece(p) {}
    virtual ~Player() = default;
    
    char getPiece() const { return piece; }
    string getName() const { return name; }
    
    virtual int getMove(const Board& board) = 0; 
};
