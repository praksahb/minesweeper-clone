#include <iostream>
#include <stack>
using namespace std;

/*
-GameBoard - will be int matrix of size (x,y)

    Public functions:-

    1. generateBoardSize(int m, int n) : used to create a board of size m,n

    2. initializegameBoard(std::pair<int, int> xycoords) : mines should not be spawned on xycoords

    3.  checkAdjacentCells((int x, int y) || std::pair<int, int> xy) - a simple function which will check all legal adjacent tiles values.
    In case of one of the tiles being 0,
    the function will be called again at the new coords.
    -making checkAdjacentCells a public function can create issues as it can be called recursively from a 0 value case.

    Private functions:
    1.1. depending on board size: no. of mines will be generated randomly. for 9*9 board generate 10 mines.
    1.2. use stack<int, int> to store location of mines.
    1.3. for each location, increment all 8 adjacent cells by 1.

    ** Remove print functions once done with class
*/
class GameBoard
{
private:
    const int mine_val = -1;
    const int mx, my;
    int maxmines;
    vector<vector<int>> board;
    stack<pair<int, int>> mines;

    // void GenerateBoardSize()
    // {
    //     board = new int *[mx];
    //     for (int i = 0; i < mx; i++)
    //     {
    //         board[i] = new int[my];
    //     }
    // }

    void InitializeWithZero()
    {
        // initialize 2d array with zero values
        for (int i = 0; i < mx; i++)
        {
            for (int j = 0; j < my; j++)
            {
                board[i][j] = 0;
            }
        }
    }

    int GetVal(int x, int y)
    {
        return board[x][y];
    }

public:
    GameBoard(int x, int y, int mines) : mx(x), my(y), maxmines(mines), board(mx, vector<int>(my, 0))
    {
    }
    ~GameBoard()
    {
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

    void prntmine()
    {
        stack<pair<int, int>> temp = mines;
        int i = 1;
        while (!temp.empty())
        {
            cout << i << '\t';
            pair<int, int> xy = temp.top();
            cout << "X: " << xy.first << '\t';
            cout << "Y: " << xy.second << '\n';
            temp.pop();
            i++;
        }
    }
    int mineCount()
    {
        int count = 0;
        for (int i = 0; i < mx; i++)
        {
            for (int j = 0; j < my; j++)
            {
                if (board[i][j] == 9)
                {
                    count++;
                }
            }
        }
        return count;
    }
    void printBoard()
    {
        for (int i = 0; i < mx; i++)
        {
            for (int j = 0; j < my; j++)
            {
                std::cout << board[i][j] << ' ';
            }
            std::cout << std::endl;
        }

        cout << "Mine Count: " << mineCount() << '\n';
    }

private:
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
};
