#include "human_player.h"
#include "AI_player.h"
#include "game_engine.h"
#include <iostream>

int main() {
    // Sample Impementation
    cout << "Initializing NEXUS4 HPC Engine...\n";

    // Player 1: Human
    HumanPlayer p1("SDE Candidate", 'X');
    // Player 2: AI 
    AIPlayer p2("Nexus AI", 'O', 9); 

    GameEngine game(&p1, &p2);

    // Start the game loop
    game.play();
}