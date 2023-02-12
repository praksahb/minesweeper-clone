#include "gameBoard.h"
using namespace std;

int main()
{
    srand(time(0));
    GameBoard new_board = GameBoard(16, 30, 99);

    // new_board.printBoard();

    new_board.fillMines(0, 0);
    new_board.printBoard();
}