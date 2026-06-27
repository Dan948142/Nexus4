#include "board.h"
#include "player.h"

class GameEngine {
private:
    Board board;
    Player* p1;
    Player* p2;
    Player* currentPlayer;

public:
    GameEngine(Player* player1, Player* player2);
    void play();
};