#include "player.h"
#include "board.h"
#include <vector>
#include <random>

struct TTEntry{
    uint64_t key;
    int score;
};

class AIPlayer : public Player {
private:
    int maxDepth;
    
    // Zobrist Hashing variables
    vector<TTEntry> transpositionTable;
    uint64_t zobristRandoms[2][49]; // 2 players, 49 board positions
    
    void initZobrist();
    uint64_t computeHash(const Board& board) const;
    
    // Minimax now takes the current hash to update it recursively
    int minimax(Board& board, int depth, int alpha, int beta, uint64_t hash);

public:
    AIPlayer(std::string n, char p, int depth = 8);
    int getMove(const Board& board) override; 
};
