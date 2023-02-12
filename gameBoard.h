#include <iostream>
#include "board.h"

using namespace std;

enum CellValue
{
    invalid = -2,
    mine = -1,
    mempty = 0,
    notempty = 1,
};

class GameBoard
{
private:
    const int mx, my;
    int maxmines;
    Board *board;

public:
    GameBoard(int x, int y, int total_mines) : mx(x), my(y), maxmines(total_mines)
    {
        board = new Board(x, y);
    }
    ~GameBoard()
    {
        delete board;
    }

    // can use return type of pointer to access location directly
    //   or create public methods in board.h to access each cell variables
    CellNode *getCellValue(int x, int y)
    {
        return board->getCellValue(x, y);
    }

    void fillMines(int start_x, int start_y)
    {
        int i = 0;
        while (i < maxmines)
        {

            int pos_x = rand() % mx;
            int pos_y = rand() & my;

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

    void printBoard()
    {
        // prints first row
        cout << endl;
        cout << "Coords   ";
        for (int i = 0; i < my; i++)
        {
            cout << "  " << i << "  ";
        }
        cout << endl;
        cout << '\t';
        for (int i = 0; i < my; i++)
        {
            cout << "-----";
        }
        cout << '-' << endl;

        for (int i = 0; i < mx; i++)
        {
            for (int j = 0; j < my; j++)
            {
                if (j == 0)
                {
                    cout << i << "\t| ";
                }
                CellNode *cell = board->getCellValue(i, j);
                if (cell->opened == false)
                {
                    if (cell->isBomb)
                    {
                        string temp = u8"\xF0\x9F\x92\xA3";

                        cout << temp << " | ";
                    }
                    else if (cell->adjacentBombs > 0)
                        cout << " " << cell->adjacentBombs << " | ";
                    else
                    {
                        cout << " " << ' ' << " | ";
                    }
                }
                else
                {
                    cout << "   | ";
                }
                cell = NULL;
            }
            cout << endl;
            cout << '\t';
            for (int j = 0; j < my; j++)
            {
                cout << "-----";
            }
            cout << '-' << endl;
        }
    }
};
