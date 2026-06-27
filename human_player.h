#include "player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer(string n, char p) : Player(n, p) {}
    int getMove(const Board& board) override; 
};
