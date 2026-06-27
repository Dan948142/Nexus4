#include "game_engine.h"
#include <iostream>

GameEngine::GameEngine(Player* player1, Player* player2) 
    : p1(player1), p2(player2), currentPlayer(player1) {}

void GameEngine::play() {
    cout << "\n--- Welcome to Stratagem4 (HPC Edition) ---\n";
    board.printBoard();

    while (true) {
        // 1. Get the move polymorphically (Human or AI)
        int col = currentPlayer->getMove(board); 
        
        // 2. Make the move. 
        board.makeMove(col); 
        
        board.printBoard();

        // 3. Check for a win.
        if (board.checkWin(board.bitboards[1])) {
            cout<<"\n🏆 " << currentPlayer->getName() << " wins in " << board.moveCount << " moves!\n";
            break;
        }
        
        if (board.isFull()) {
            cout << "\n🤝 It's a draw!\n";
            break;
        }

        // 4. Swap turns for the UI Controller
        currentPlayer = (currentPlayer == p1) ? p2 : p1;
    }
}