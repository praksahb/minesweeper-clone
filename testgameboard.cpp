#include "gameBoard.h"
using namespace std;

int main()
{
    srand(time(0));
    GameBoard new_board = GameBoard(15, 15, 40);

    // new_board.printBoard();

    new_board.fillMines(7, 7);
    new_board.printBoard();
}