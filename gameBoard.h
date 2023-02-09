#include <iostream>
#include <stack>
using namespace std;

class GameBoard
{
private:
    const int mine_val = -1;
    const int mx, my;
    int maxmines;
    vector<vector<int>> board;
    stack<pair<int, int>> mines;

    int GetVal(int x, int y)
    {
        return board[x][y];
    }

    void IncrementAdjacents(pair<int, int> xy)
    {
        // increment all adjacents by 1 if adjacents is not a bomb itself
        for (int i = xy.first - 1; i <= xy.first + 1; i++)
        {
            for (int j = xy.second - 1; j <= xy.second + 1; j++)
            {
                // boundary check
                if (i >= 0 && i < mx && j >= 0 && j < my)
                {
                    // bomb check
                    if (board[i][j] != 9 && !(i == xy.first && j == xy.second))
                    {
                        board[i][j]++;
                    }
                }
            }
        }
    }

public:
    GameBoard(int x, int y, int mines) : mx(x), my(y), maxmines(mines), board(mx, vector<int>(my, 0))
    {
    }
    ~GameBoard()
    {
    }

    stack<pair<int, int>> getMines()
    {
        return mines;
    }

    int getCellValue(int x, int y)
    {
        // invalid index
        if (x < 0 && x >= mx && y < 0 && y >= my)
        {
            return -2;
        }

        return GetVal(x, y);
    }

    // not very space optimum O(2^n) where n = no. of mines
    void fillMines(pair<int, int> xy)
    {
        if (mines.size() == maxmines)
        {
            return;
        }
        int x = (rand() % mx);
        int y = (rand() % my);

        if (x == xy.first && y == xy.second || board[x][y] != 0)
        {
            fillMines(xy);
        }
        else
        {
            board[x][y] = mine_val;
            mines.push({x, y});
            fillMines(xy);
        }
    }

    void incrementAdjacents()
    {
        stack<pair<int, int>> temp = mines;

        while (!temp.empty())
        {
            // get mine location
            pair<int, int> xy = temp.top();
            IncrementAdjacents(xy);
            temp.pop();
        }
    }
};
