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
};

class PlayBoard
{
    const int mx, my;
    std::vector<std::vector<char>> board;
    vector<vector<bool>> visited;
    GameBoard *gboard;
    int winCondition;
    int visitedNodes;
    GameState gameState;

    int directionX[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int directionY[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

public:
    PlayBoard(int x, int y, int mines) : mx(x),
                                         my(y),
                                         board(mx, vector<char>(my, ' ')),
                                         visited(mx, vector<bool>(my, false))
    {
        winCondition = mx * my - mines;
        gboard = new GameBoard(x, y, mines);
        visitedNodes = 0;
        gameState = newGame;
    }

    GameState getState()
    {
        return gameState;
    }

    bool gameWon()
    {
        return visitedNodes >= winCondition;
    }

    void initializeGameBoard(int x, int y)
    {
        gboard->fillMines({x, y});
        gboard->incrementAdjacents();
        // openCell(x, y);
        checkCellDFS(x, y);
        gameState = on;
    }

    void setState(GameState gs)
    {
        gameState = gs;
    }

    void checkCellDFS(int x, int y)
    {
        // initialize temp stack
        stack<pair<int, int>> stk;
        stk.push({x, y});

        while (!stk.empty())
        {
            pair<int, int> curr = stk.top();
            stk.pop(); // pop early to avoid it duplicating. or use queue
            int x = curr.first;
            int y = curr.second;
            // check if valid location
            if (x >= 0 && x < mx && y >= 0 && y < my)
            {
                // check if location not yet checked
                if (visited[x][y] == false)
                {
                    // check value from gboard
                    int val = gboard->getCellValue(x, y);
                    if (val == mempty)
                    {
                        board[x][y] = '0';
                        visited[x][y] = true;
                        visitedNodes++;
                        for (int i = 0; i < 8; i++)
                        {
                            // add adjacent x,y values to stack
                            int adjx = x + directionX[i];
                            int adjy = y + directionY[i];
                            stk.push({adjx, adjy});
                        }
                    }
                    else if (val == mine)
                    {
                        board[x][y] = 'X';
                        visitedNodes++;
                        // bomb hit exit loop change bool values
                        gameState = off;
                        return;
                    }
                    else
                    {
                        // value is no. of bombs around it
                        board[x][y] = static_cast<char>(val + '0');
                        visited[x][y] = true;
                        visitedNodes++;
                    }
                }
            }
        }
    }

    // recursive function - not working
    void checkCell(int x, int y)
    {
        // check if x and y are legal
        if (x < 0 || y < 0 || x >= mx || y >= my)
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
        for (int i = 0; i < my; i++)
        {
            cout << " " << i << "  ";
        }
        cout << endl;
        cout << '\t';
        for (int i = 0; i < my; i++)
        {
            cout << "----";
        }
        cout << '-' << endl;

        for (int i = 0; i < mx; i++)
        {
            for (int j = 0; j < my; j++)
            {
                if (j == 0)
                {
                    cout << i << "\t|";
                }
                cout << " " << board[i][j] << " |";
            }
            cout << endl;
            cout << '\t';
            for (int j = 0; j < my; j++)
            {
                cout << "----";
            }
            cout << '-' << endl;
        }
    }
};

// printBoard original function
/*
 void printBoard()
    {
        cout << "-------------------------------------------" << endl;

        for (int i = 0; i < mx; i++)
        {
            for (int j = 0; j < my; j++)
            {
                if (j == 0)
                    cout << "|     |";
                cout << " " << board[i][j] << " |";
            }
            cout << endl;
            cout << "-------------------------------------------" << endl;
            for (int j = 0; j < my; j++)
            {
                if (j == 0)
                    cout << "| x,y |";
                cout << i << "," << j << "|";
            }
            cout << endl;
            cout << "-------------------------------------------" << endl;
        }
    }
*/