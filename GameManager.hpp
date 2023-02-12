#include "gameBoard.h"

class GameManager
{
private:
    GameState gameChecker;
    GameBoard *playingBoard; // display board
    int rows, col, maxmines;

    // private functions
    int gameMenu()
    {
        cout << "===================================\n\n";
        cout << "Minesweeper Clone:\n\n";
        cout << "===================================\n\n";
        cout << "Choose Options:\n1. Play Game\n2. Change board size\n3. Exit\n";
        cout << "Enter Choice: ";
        int n = 0;
        cin >> n;
        cout << endl;
        return n;
    }

    // change Difficulty
    void changeBoardSize()
    {
        cout << "Choose the difficulty level:\n";
        cout << "1. Beginner: (9*9) cells, 10 mines.\n";
        cout << "2. Intermediate: (16*16) cells, 40 mines.\n";
        cout << "3. Expert: (30*16) cells, 99 mines.\n";
        cout << "Enter your choice: ";
        int n = 0;
        cin >> n;
        if (n == 1)
        {
            rows = 9, col = 9, maxmines = 10;
        }
        else if (n == 2)
        {
            rows = 16, col = 16, maxmines = 40;
        }
        else
        {
            rows = 30, col = 16, maxmines = 99;
        }
        cout << endl;
    }

    //
    pair<int, int> TakeInput()
    {
        int rowX = rows, colY = col;
        while (rowX < 0 || colY < 0 || rowX >= rows || colY >= col)
        {
            cout << "Enter value for x and y(space-separated): ";
            cin >> rowX;
            cin >> colY;
        }
        return {rowX, colY};
    }

    //
    void playTurn(GameState val)
    {
        cout << "How To Play:\n- Input x(rowno.) and y(column no:):\n";
        pair<int, int> xy = TakeInput();
        if (val == newGame)
        {
            playingBoard->initializeGameBoard(xy.first, xy.second);
            return;
        }
        if (val == on)
        {
            playingBoard->checkCellDFS(xy.first, xy.second);
        }
    }

public:
    // Default constructor
    GameManager()
    {
        rows = 9;
        col = 9;
        maxmines = 10;
        gameChecker = newGame;
    }
    // public functions
    void runLoops()
    {
        // create a main outer loop
        while (true)
        {
            int n = gameMenu();
            // Play the game
            if (n == 1)
            {
                // col and row values are to be interchanged
                // or make subsequent changes to logic
                // in print function in gameBoard
                playingBoard = new GameBoard(col, rows, maxmines);
                gameChecker = playingBoard->getState();

                // main game loop
                while (gameChecker == newGame || gameChecker == on)
                {
                    playingBoard->printBoard();
                    playTurn(gameChecker);
                    gameChecker = playingBoard->getState();
                }

                playingBoard->printBoard();
                if (gameChecker == gameWon)
                {
                    cout << "Congrats. Game won.\n";
                }
                else
                {
                    cout << "Touched a Mine.\nGame Over.\n";
                }
            }
            else if (n == 2)
            {
                // change Difficulty
                changeBoardSize();
            }
            else
            {
                break;
            }
        }
    }
};
