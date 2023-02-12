#include <vector>
#include "cellNode.h"

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
        // board = std::vector<std::vector<CellNode>>(max_rows, std::vector<CellNode>(max_cols, CellNode()));
    }

    void initializeBoard()
    {

        for (int i = 0; i < max_rows; i++)
        {
            std::vector<CellNode> temp;
            for (int j = 0; j < max_cols; j++)
            {
                // non dynamic allocation
                // board[max_rows][max_cols] = CellNode();
                CellNode tempNode;
                temp.push_back(CellNode());
            }
            board.push_back(temp);
        }
    }

    // add values to the board :-
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
            int adjX = x + directionX[i];
            int adjY = y + directionY[i];
            if (checkForInvalidLocation(adjX, adjY) == false)
            {
                if (board[adjX][adjY].isBomb == false)
                {
                    board[adjX][adjY].adjacentBombs += 1;
                }
            }
        }
    }
    // 3. Get Value(s) of cell.
    CellNode *getCellValue(int x, int y)
    {
        if (checkForInvalidLocation(x, y) == false)
        {
            return &board[x][y];
        }
        else
        {
            // return null - node not found
            return new CellNode(0);
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
    void markVisited(int pos_x, int pos_y)
    {
        if (!checkForInvalidLocation(pos_x, pos_y))
        {
            board[pos_x][pos_y].visited = true;
        }
    }

    // 6. change cellnode.opened - for print functionality
};
