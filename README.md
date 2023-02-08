Minesweeper: 

**[Rules]**

- The board is divided into cells, with mines randomly distributed.
- To win, you need to open all the cells.
- The number on a cell shows the number of mines adjacent to it. Using this information, you can determine cells that are safe, and cells that contain mines.

Implementation: 

Main classes to be created: 

-Player- will have one function mainly.
    1. stl::pair<int, int> inputXY(int x, int y) : returns x,y values(internally should check if legal values(>= 0 && < x || y))  
    2. (Additional/Secondary) : void putFlag(int x, int y)

-DisplayBoard/ playBoard - will show the board in the console 
displayBoard would be a 2d vector of char type.

    1. printBoard() will be printing the whole board of size (m,n)

    - Use stack for storing adjacent cells x,y coords
    2. checkCell(int x, int y) function should be checking the valid x,y values in the gameBoard for int comparisons checking for:-
        -1 for bomb,
        0 for no adjacent bombs,
        positive int value which signifies no. of bombs in adjacency.

-GameBoard - will be int matrix of size (x,y)
    Public functions:-
    1. generateBoardSize(int m, int n) : used to create a board of size m,n
    2. initializegameBoard(std::pair<int, int> xycoords) : mines should not be spawned on xycoords
        2.1. FillMines (user inputs value)
        2.2. IncrementAdjacents() for each location, increment all 8 adjacent cells by 1.

    Private functions:
    1.2. use stack<int, int> to store location of mines.
