Minesweeper: 

**[Rules]**

- The board is divided into cells, with mines randomly distributed.
- To win, you need to open all the cells.
- The number on a cell shows the number of mines adjacent to it. Using this information, you can determine cells that are safe, and cells that contain mines.
- Interact, evolve and enjoy!

**[Task]**

- Create a board of any size n * n, such that n ≥ 9.
- You should take two integers x and y (where the player want to click) as input from the user(player).
- Remember whatever the first input is given by the user that place should not contain the mine i.e. generate the board and number on the board after taking the first input.
- After each input shows the updated status of the board and asks the user to input the next step.
- The game should run until either player loses the game or wins the game.
- Use OOPs concepts
- **The deadline for completing this assignment is of 4 days from the day you start.**

Implementation: 

Main classes to be created: 

-Player- will have one function mainly.
    1. stl::pair<int, int> inputXY(int x, int y) : returns x,y values(internally should check if legal values(>= 0 && < x || y))  
    2. (Additional/Secondary) : void putFlag(int x, int y)

-DisplayBoard - will show the board in the console //(instead of being a seperate class displayBoard can be implemented inside Gameboard class- will solve access issues for the 2nd unnamed function)
displayBoard would be a character array or string array.

    1. printBoard() will be printing the whole board of size (m,n)

    2. Unnamed function(stl::pair<int, int> val): Player::inputXY(x,y) should trigger this function to run which should be checking the valid x,y values in the gameBoard for int comparisons checking for:-
        -1 for bomb,
        0 for no adjacent bombs,
        positive int value which signifies no. of bombs in adjacency.
    This function is going to need access to the gameBoard class for getting its values at the index. 
    And for a value of 0 it should be running a checkAdjacentCells() functions for the current value. 

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
