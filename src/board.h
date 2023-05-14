#include <vector>

// cell DS in board
struct CellNode
{
    int adjacentBombs;
    bool isBomb;
    bool visited;

public:
    CellNode()
    {
        adjacentBombs = 0;
        isBomb = false;
        visited = false;
    }
};

class Board
{
    std::vector<std::vector<CellNode>> board;
    int max_rows, max_cols;

    int directionX[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int directionY[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

public:
    Board(int x, int y) : max_rows(x), max_cols(y)
    {
        initializeBoard();
    }

    void initializeBoard()
    {

        for (int i = 0; i < max_rows; i++)
        {
            std::vector<CellNode> temp;
            for (int j = 0; j < max_cols; j++)
            {
                // non dynamic allocation
                temp.push_back(CellNode());
            }
            board.push_back(temp);
        }
    }

    // Public functions
    // 1. add mines to the board
    int addMine(int rowno, int colno, int start_x, int start_y)
    {
        if (checkForInvalidLocation(rowno, colno))
        {
            return 0;
        }

        if (board[rowno][colno].isBomb == false && !(rowno == start_x && colno == start_y))
        {
            board[rowno][colno].isBomb = true;
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
            int adjX = x + getDirX(i);
            int adjY = y + getDirY(i);
            if (checkForInvalidLocation(adjX, adjY) == false)
            {
                if (board[adjX][adjY].isBomb == false)
                {
                    board[adjX][adjY].adjacentBombs += 1;
                }
            }
        }
    }
    // 4.Reset cell value - adjacentbombs
    void resetValue(int x, int y)
    {
        if (checkForInvalidLocation(x, y) == false)
        {
            board[x][y].adjacentBombs = 0;
        }
    }
    // 5. change node.visited to true
    void setVisited(int pos_x, int pos_y)
    {
        if (!checkForInvalidLocation(pos_x, pos_y))
        {
            board[pos_x][pos_y].visited = true;
        }
    }

    // 6. getters
    bool isCellVisited(int x, int y)
    {
        if (!checkForInvalidLocation(x, y))
        {
            return board[x][y].visited;
        }
        return false;
    }

    bool isCellBomb(int x, int y)
    {
        if (!checkForInvalidLocation(x, y))
        {
            return board[x][y].isBomb;
        }
        return false;
    }
    int getAdjBombs(int x, int y)
    {
        if (!checkForInvalidLocation(x, y))
        {
            return board[x][y].adjacentBombs;
        }
        return -1;
    }
    int getDirX(int i)
    {
        if (i >= 0 && i < 8)
        {
            return directionX[i];
        }
        return -1;
    }
    int getDirY(int i)
    {
        if (i >= 0 && i < 8)
        {
            return directionY[i];
        }
        return -1;
    }
};
