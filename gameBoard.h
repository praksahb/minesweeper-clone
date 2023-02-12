#include <iostream>
#include <stack>
#include "board.h"

using namespace std;

enum GameState
{
    off = -1,
    newGame = 0,
    on = 1,
    gameWon,
    gameLost,
};

class GameBoard
{
private:
    const int max_rows, max_cols;
    int maxmines;
    Board *board;
    GameState gameState;
    int visitedNodes;
    int totalValidCells;

public:
    GameBoard(int x, int y, int total_mines) : max_rows(x), max_cols(y), maxmines(total_mines)
    {
        board = new Board(x, y);
        gameState = newGame;
        totalValidCells = max_rows * max_cols - total_mines;
        visitedNodes = 0;
    }
    ~GameBoard()
    {
        delete board;
    }
    GameState getState()
    {
        return gameState;
    }

    void initializeGameBoard(int start_x, int start_y)
    {
        fillMines(start_x, start_y);
        gameState = on;
        checkCellDFS(start_x, start_y);
    }

    void fillMines(int start_x, int start_y)
    {
        int i = 0;
        while (i < maxmines)
        {

            int pos_x = rand() % max_rows;
            int pos_y = rand() % max_cols;

            // return values: 0 is invalid,
            // 1 is correct and
            // -1 is already mine
            int val = board->addMine(pos_x, pos_y, start_x, start_y);
            if (val == 1)
            {
                i++;
                // reset cellNode.adjacentBombs value
                board->resetValue(pos_x, pos_y);
                board->incrementAdjacents(pos_x, pos_y);
            }
        }
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
            int pos_x = curr.first;
            int pos_y = curr.second;
            // check if valid location
            if (pos_x >= 0 && pos_x < max_rows && pos_y >= 0 && pos_y < max_cols)
            {
                // if cell is not visited yet
                if (board->isCellVisited(pos_x, pos_y) == false)
                {
                    bool isCellBomb = board->isCellBomb(pos_x, pos_y);

                    // Case 1 - bomb in cell
                    if (isCellBomb == true)
                    {
                        // update all cells
                        gameState = gameLost;
                        return;
                    }

                    int adjBombs = board->getAdjBombs(pos_x, pos_y);

                    // Case 2.1 - blank cell
                    if (!isCellBomb && adjBombs == 0)
                    {
                        board->setVisited(pos_x, pos_y);
                        visitedNodes++;
                        if (visitedNodes == totalValidCells)
                        {
                            // update all cells
                            gameState = gameWon;
                            return;
                        }
                        // add all 8 adjacent x,y values to stack
                        for (int i = 0; i < 8; i++)
                        {
                            int adjx = pos_x + board->getDirX(i);
                            int adjy = pos_y + board->getDirY(i);
                            stk.push({adjx, adjy});
                        }
                    }
                    // Case 2.2 - Number in cell
                    if (!isCellBomb && adjBombs > 0)
                    {
                        // value is no. of bombs around it (maxVal == 8)
                        board->setVisited(pos_x, pos_y);
                        visitedNodes++;
                        if (visitedNodes == totalValidCells)
                        {
                            // update all cells
                            gameState = gameWon;
                        }
                    }
                }
            }
        }
    }

    void PrintFirstRow()
    {
        // prints first row
        cout << '\n';
        cout << "Coords   ";
        for (int i = 0; i < max_cols; i++)
        {
            if (i < 10)
            {
                cout << " ";
            }
            cout << ' ' << i << "  ";
        }
        cout << '\n';
        cout << '\t';
        for (int i = 0; i < max_cols; i++)
        {
            cout << "-----";
        }
        cout << '-' << '\n';
    }

    void PrintMatrix()
    {
        // prints the matrix

        for (int i = 0; i < max_rows; i++)
        {
            for (int j = 0; j < max_cols; j++)
            {
                if (j == 0)
                {
                    cout << i << "\t| ";
                }
                // can use cell.visited instead
                if (gameState == newGame || gameState == on)
                {
                    if (board->isCellVisited(i, j) == true) // will be true for in game
                    {
                        if (board->isCellBomb(i, j))
                        {
                            string temp = "*";
                            cout << " * | ";
                        }
                        else
                        {
                            cout << ' ' << board->getAdjBombs(i, j) << " | ";
                        }
                    }
                    else
                    {
                        cout << "   | ";
                    }
                }
                else
                {
                    if (board->isCellBomb(i, j))
                    {
                        char temp = '*';
                        cout << ' ' << temp << " | ";
                    }
                    else
                    {
                        cout << ' ' << board->getAdjBombs(i, j) << " | ";
                    }
                }
            }
            // prints a line underneath
            cout << '\n';
            cout << '\t';
            for (int j = 0; j < max_cols; j++)
            {
                cout << "-----";
            }
            cout << '-' << '\n';
        }
    }

    void printBoard()
    {
        PrintFirstRow();
        PrintMatrix();
    }
};
