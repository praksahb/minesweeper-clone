#include <iostream>
#include <stack>
using namespace std;

enum CellValue
{
    invalid = -2,
    mine = -1,
    mempty = 0,
    notempty = 1,
};

class Board
{
    vector<vector<int>> board;
    int max_rows, max_cols;

    int directionX[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int directionY[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

public:
    Board(int x, int y) : max_rows(x), max_cols(y), board(max_rows, vector<int>(max_cols, 0))
    {
    }

    // add values to the board :-
    // Public functions
    // 1. add mines to the board
    int addMine(int rowno, int colno)
    {
        if (checkForInvalidLocation(rowno, colno))
        {
            return 0;
        }

        if (board[rowno][colno] >= 0)
        {
            board[rowno][colno] = mine;
            return 1;
        }
        else
        {
            return -1;
        }
    }

    bool checkForInvalidLocation(int x, int y)
    {
        if (x < 0 || y < 0 || x >= max_rows || y >= max_cols)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // 2. increment all the cells values by 1 adjacent to a mine
    // if not a mine itself
    void incrementAdjacents(int x, int y)
    {
        for (int i = 0; i < 8; i++)
        {
            int adjX = x + directionX[i];
            int adjY = y + directionY[i];
            if (!checkForInvalidLocation(adjX, adjY))
            {
                if (board[adjX][adjY] >= 0)
                {
                    board[adjX][adjY]++;
                }
            }
        }
    }
    // 3. int return Get Value of cell.
    int getCellValue(int x, int y)
    {
        if (checkForInvalidLocation(x, y) == false)
        {
            return board[x][y];
        }
        else
        {
            return -2;
        }
    }
};

class GameBoard
{
private:
    const int mine_val = -1;
    const int mx, my;
    int maxmines;
    Board board;
    stack<pair<int, int>> mine_stk;

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
                    if (board[i][j] != mine_val && !(i == xy.first && j == xy.second))
                    {
                        board[i][j]++;
                    }
                }
            }
        }
    }

public:
    GameBoard(int x, int y, int total_mines) : mx(x), my(y), maxmines(total_mines), board(mx, vector<int>(my, 0))
    {
    }
    ~GameBoard()
    {
    }

    stack<pair<int, int>> getMines()
    {
        return mine_stk;
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
        if (mine_stk.size() == maxmines)
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
            mine_stk.push({x, y});
            fillMines(xy);
        }
    }

    void incrementAdjacents()
    {
        stack<pair<int, int>> temp = mine_stk;

        while (!temp.empty())
        {
            // get mine location
            pair<int, int> xy = temp.top();
            IncrementAdjacents(xy);
            temp.pop();
        }
    }
};
