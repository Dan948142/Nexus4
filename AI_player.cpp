#include <limits>
#include <algorithm>
#include <iostream>
#include "AI_player.h"

AIPlayer::AIPlayer(string n, char p, int depth) : Player(n, p), maxDepth(depth) {
    transpositionTable.resize(8388593, {0, 0}); 
    initZobrist();
}

void AIPlayer::initZobrist() {
    mt19937_64 rng(1337); 
    for (int p = 0; p < 2; ++p) {
        for (int i = 0; i < 49; ++i) {
            zobristRandoms[p][i] = rng();
        }
    }
}

uint64_t AIPlayer::computeHash(const Board& board) const {
    uint64_t hash = 0;
    for (int c = 0; c < 7; ++c) {
        for (int r = 0; r < 6; ++r) {
            uint64_t mask = 1ULL << (c * 7 + r);
            if (board.bitboards[0] & mask) hash ^= zobristRandoms[0][c * 7 + r];
            if (board.bitboards[1] & mask) hash ^= zobristRandoms[1][c * 7 + r];
        }
    }
    return hash;
}

int AIPlayer::minimax(Board& board, int depth, int alpha, int beta, uint64_t hash) {
    int ttIndex = hash % transpositionTable.size();
    if(transpositionTable[ttIndex].key == hash){
        return transpositionTable[ttIndex].score; 
    }

    if (board.checkWin(board.bitboards[1])) return -1000000 + (maxDepth - depth);
    if (board.isFull()) return 0;
    if (depth == 0) return 0; 

    int maxEval = numeric_limits<int>::min();
    
    int colOrder[] = {3, 2, 4, 1, 5, 0, 6};
    
    for (int col : colOrder) {
        if (board.isValidMove(col)) {
            Board nextBoard = board; 
            nextBoard.makeMove(col);
            
            uint64_t nextHash = hash ^ zobristRandoms[0][board.height[col]]; 
            
            int eval = -minimax(nextBoard, depth - 1, -beta, -alpha, nextHash);
            
            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            if (alpha >= beta) break; 
        }
    }

    transpositionTable[ttIndex] = {hash, maxEval};
    return maxEval;
}

int AIPlayer::getMove(const Board& current_board) {
    cout << name << " (" << piece << ") is computing state space...\n";
    
    int bestScore = numeric_limits<int>::min();
    int bestCol = 3;
    
    int colOrder[] = {3, 2, 4, 1, 5, 0, 6};
    uint64_t baseHash = computeHash(current_board);

    for (int col : colOrder) {
        if (current_board.isValidMove(col)) {
            Board nextBoard = current_board;
            nextBoard.makeMove(col);
            
            uint64_t nextHash = baseHash ^ zobristRandoms[0][current_board.height[col]];
            
            // Kick off recursion
            int score = -minimax(nextBoard, maxDepth - 1, numeric_limits<int>::min() + 1, numeric_limits<int>::max(), nextHash);
            
            if (score > bestScore) {
                bestScore = score;
                bestCol = col;
            }
        }
    }
    return bestCol;
}