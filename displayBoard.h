#include <iostream>
#include <vector>
#include <stack>
#include "gameBoard.h"

enum GameState
{
    off = -1,
    newGame = 0,
    on = 1,
    gameWon,
    gameLost,
};

// game board / display board
class DisplayBoard
{
    const int maxXrows, maxYcols;
    std::vector<std::vector<char>> board;
    GameBoard *gboard;
    int winCondition;
    int visitedNodes;
    GameState gameState;

    int directionX[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int directionY[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

public:
    DisplayBoard(int x, int y, int mines) : maxXrows(x),
                                            maxYcols(y),
                                            board(maxXrows, vector<char>(maxYcols, ' '))
    {
        winCondition = maxXrows * maxYcols - mines;
        gboard = new GameBoard(x, y, mines);
        visitedNodes = 0;
        gameState = newGame;
    }
    virtual ~DisplayBoard()
    {
        delete gboard;
    }

    GameState getState()
    {
        return gameState;
    }

    void initializeGameBoard(int x, int y)
    {
        gboard->fillMines(x, y);
        gameState = on;
        checkCellDFS(x, y);
    }

    void checkCellDFS(int x, int y)
    {
        // initialize empty temp stack
        stack<pair<int, int>> stk;
        stk.push({x, y});

        while (!stk.empty())
        {
            pair<int, int> curr = stk.top();
            stk.pop(); // pop early to avoid it duplicating. or use queue?
            int x = curr.first;
            int y = curr.second;
            // check if valid location
            if (x >= 0 && x < maxXrows && y >= 0 && y < maxYcols)
            {
                // check value from gboard
                CellNode *val = gboard->getCellValue(x, y);
                cout << "Val.adj: " << val->adjacentBombs << '\n';
                // check if location not yet checked
                if (val->visited == false)
                {
                    // Case 1 - bomb in cell
                    if (val->isBomb == true)
                    {
                        // updateAllMines();
                        gameState = gameLost;
                        return;
                    }

                    // Case 1.1 - blank cell
                    if (val->isBomb == false && val->adjacentBombs == 0)
                    {
                        board[x][y] = '0';
                        val->visited = true;
                        visitedNodes++;

                        if (visitedNodes == winCondition)
                        {
                            // update all cells
                            // updateAllMines();
                            gameState = gameWon;
                            return;
                        }
                        // add all 8 adjacent x,y values to stack
                        for (int i = 0; i < 8; i++)
                        {
                            int adjx = x + directionX[i];
                            int adjy = y + directionY[i];
                            stk.push({adjx, adjy});
                        }
                    }
                    // Case 1.2 - Number in cell
                    if (val->isBomb == false && val->adjacentBombs > 0)
                    {
                        // value is no. of bombs around it (maxVal == 8)
                        board[x][y] = static_cast<char>(val->adjacentBombs + '0');
                        val->visited = true;
                        visitedNodes++;
                        if (visitedNodes == winCondition)
                        {
                            // update all cells
                            gameState = gameWon;
                        }
                    }
                }
            }
        }
    }

    void printBoard()
    {
        cout << endl;
        cout << "Coords   ";
        for (int i = 0; i < maxYcols; i++)
        {
            cout << " " << i << "  ";
        }
        cout << endl;
        cout << '\t';
        for (int i = 0; i < maxYcols; i++)
        {
            cout << "----";
        }
        cout << '-' << endl;

        for (int i = 0; i < maxXrows; i++)
        {
            for (int j = 0; j < maxYcols; j++)
            {
                if (j == 0)
                {
                    cout << i << "\t|";
                }
                cout << " " << board[i][j] << " |";
            }
            cout << endl;
            cout << '\t';
            for (int j = 0; j < maxYcols; j++)
            {
                cout << "----";
            }
            cout << '-' << endl;
        }
    }
};
