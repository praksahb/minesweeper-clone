#include <iostream>
#include <vector>
#include "gameBoard.h"

enum CellValue
{
    invalid = -2,
    mine = -1,
    mempty = 0,
    notempty,
};

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
    vector<vector<bool>> visited;
    GameBoard *gboard;
    int winCondition;
    int visitedNodes;
    GameState gameState;

    int directionX[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int directionY[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

public:
    DisplayBoard(int x, int y, int mines) : maxXrows(x),
                                            maxYcols(y),
                                            board(maxXrows, vector<char>(maxYcols, ' ')),
                                            visited(maxXrows, vector<bool>(maxYcols, false))
    {
        winCondition = maxXrows * maxYcols - mines;
        gboard = new GameBoard(x, y, mines);
        visitedNodes = 0;
        gameState = newGame;
    }

    GameState getState()
    {
        return gameState;
    }

    void initializeGameBoard(int x, int y)
    {
        gboard->fillMines({x, y});
        gboard->incrementAdjacents();
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
                // check if location not yet checked
                if (visited[x][y] == false)
                {
                    // check value from gboard
                    int val = gboard->getCellValue(x, y);

                    // Case 1 - blank cell
                    if (val == mempty)
                    {
                        board[x][y] = '0';
                        visited[x][y] = true;
                        if (++visitedNodes == winCondition)
                        {
                            updateAllMines();
                            gameState = gameWon;
                        }
                        // add all 8 adjacent x,y values to stack
                        for (int i = 0; i < 8; i++)
                        {
                            int adjx = x + directionX[i];
                            int adjy = y + directionY[i];
                            stk.push({adjx, adjy});
                        }
                    }
                    // Case 2 - bomb in cell
                    else if (val == mine)
                    {
                        updateAllMines();
                        gameState = off;
                        return;
                    }
                    // Case 3 - Number in cell
                    else
                    {
                        // value is no. of bombs around it (maxVal == 8)
                        board[x][y] = static_cast<char>(val + '0');
                        visited[x][y] = true;
                        if (++visitedNodes == winCondition)
                        {
                            updateAllMines();
                            gameState = gameWon;
                        }
                    }
                }
            }
        }
    }

    void updateAllMines()
    {
        // use stack of mines to display all the mines.
        // try without using a copy of stack
        stack<pair<int, int>> temp = gboard->getMines();
        while (!temp.empty())
        {
            pair<int, int> xy = temp.top();
            board[xy.first][xy.second] = 'X';
            temp.pop();
        }
    }

    // recursive function - not working
    void checkCell(int x, int y)
    {
        // check if x and y are legal
        if (x < 0 || y < 0 || x >= maxXrows || y >= maxYcols)
        {
            return;
        }

        if (visited[x][y] == true)
        {
            return;
        }

        // get value of board[x][y]
        int val = gboard->getCellValue(x, y);

        // not needed
        if (val == -2)
        {
            // invalid cell location
            return;
        }

        // val == bomb
        if (val == -1)
        {
            // bomb opened
            gameState = off;
            board[x][y] = 'X';
            visited[x][y] = true;
            visitedNodes++;
            return;
        }

        if (val == 0)
        {
            // empty cell opened
            board[x][y] = '0';
            visited[x][y] = true;
            visitedNodes++;

            // open adjacent cells
            for (int i = 0; i < 8; i++)
            {
                int adjx = directionX[i];
                int adjy = directionY[i];
                checkCell(adjx, adjy);
            }
        }
        else
        {
            // val = no. of mines in adjacency
            board[x][y] = static_cast<char>(val + '0');
            visited[x][y] = true;
            visitedNodes++;
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
