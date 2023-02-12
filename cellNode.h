
// cell in board

struct CellNode
{
    int adjacentBombs;
    bool isBomb;
    bool visited;
    bool opened;
    bool invalid;

public:
    CellNode()
    {
        adjacentBombs = 0;
        isBomb = false;
        visited = false;
        opened = false;
        invalid = false;
    }

    CellNode(int x)
    {
        adjacentBombs = x;
        isBomb = false;
        visited = false;
        opened = false;
        invalid = true;
    }
};