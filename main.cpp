#include "GameManager.hpp"

void runGame()
{
    srand(time(0));
    GameManager *gameManager = new GameManager();
    gameManager->runLoops();
}

int main()
{
    runGame();
}