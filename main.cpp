#include <bits/stdc++.h>
#include "board.hpp"

int main()
{
    srand(time(0));
    GameBoard *b = new GameBoard(9, 9, 10);
    b->fillMines({2, 0});
    b->incrementAdjacents();
    b->printBoard();
    b->prntmine();
    delete b;
}