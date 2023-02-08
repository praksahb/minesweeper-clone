#include <iostream>
#include "playBoard.h"

void gameLoop()
{
    srand(time(0));

    // create a game loop
    GameState gameState = on;
    while (true)
    {
        cout << "Minesweeper Clone:\n";
        cout << "Choose Options:\n1. Play Game\n2. Exit\n";
        cout << "Enter Choice: ";
        int n = 0;
        cin >> n;
        cout << endl;
        if (n == 1)
        {
            int x = 0, y = 0, mines = 0;
            cout << "Enter width: ";
            cin >> y;
            cout << "\nEnter height: ";
            cin >> x;
            cout << "\nEnter no. of mines: ";
            cin >> mines;
            cout << endl;
            PlayBoard *pb = new PlayBoard(x, y, mines);
            while (pb->getState() != off)
            {
                pb->printBoard();
                cout << "How To Play:\n- User will input x and y(coordinates where they want to click)\n";
                cout << "Enter value for x and y: ";
                int x = 0, y = 0;
                cin >> x >> y;
                cout << endl;

                if (pb->getState() == newGame)
                {
                    pb->initializeGameBoard(x, y);
                }
                else
                {
                    pb->checkCellDFS(x, y);
                }
                if (pb->gameWon() == true)
                {
                    pb->setState(off);
                }
            }
            pb->printBoard();
            if (pb->gameWon() == false)
            {
                cout << "Touched a Mine.\nGame Over.\n";
            }
            else
            {
                cout << "Congrats. Game won.\n";
            }
        }
        else
        {
            break;
        }
    }
}

int main()
{
    gameLoop();
}