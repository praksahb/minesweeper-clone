Minesweeper: 

**[Rules]**

- The board is divided into cells, with mines randomly distributed.
- To win, you need to open all the cells.
- The number on a cell shows the number of mines adjacent to it. Using this information, you can determine cells that are safe, and cells that contain mines.

Implementation: 

Main classes: 

#1. Board - Contains cell struct (cellNode) and 2d vector board of type CellNode.
   Main functions for connecting with the board values:-
   - change cellNode values in board.
   		-  get/set bool isBomb
     	-  get/set int Adjacent Bombs
     	-  mark visited true
   - check for invalid values of x,y(indexes of 2d vector)

#2. GameBoard - will be responsible for game logic, also using enum gameState to store current state of game. 
   
	2 Main Functions:
   		-  checkCellDFS - using stack to store position of players move and open up board
		- initializeGameBoard - will create a random board after taking first input of pos_x and pos_y from user
	 		-  fillMines - fills mines by connecting with board class

 		-  Helper function: Print/Display Board for displaying on cli

#3. GameManager - will  handle the logic for playing the game with player with help of gameBoard and gameState
   - Main Functions:
   		- runLoops - will run two while loops for playing game.
     	- changeBoardSize - 3 difficulties cannot use custom values for row and columns
     	- playTurn and takeinput for playing a turn


