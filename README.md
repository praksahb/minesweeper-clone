# Minesweeper Clone 
## Objective and Description
Minesweeper clone is a command-line based game application that replicates the classic Minesweeper game found on Windows operating systems. The objective of the game is to clear a minefield without detonating any hidden mines. The game is built using C++ programming language and runs on the command line interface (CLI).

Play on repl: https://replit.com/@praksahb/Minesweeper-clone

## Key Features
The game has three difficulty levels (beginner, intermediate, and expert) that affect the size of the minefield and the number of mines hidden within it.

## Implementation Details
This Minesweeper clone is built using object-oriented programming (OOP) concepts and uses a two-dimensional vector to represent the minefield. The project contains two main classes: Board and GameBoard. Board includes a cellNode struct and a 2D vector of cellNodes that represent the game board. The class provides functions for checking the validity of cell indexes, changing cellNode values in the board, and marking a cell as visited.

GameBoard is responsible for implementing the game logic, including using an enum gameState to keep track of the current state of the game. The class contains two main functions: checkCellDFS which uses a stack-based algorithm to store the player's moves and open up the board, and initializeGameBoard which creates a random board after taking the first input of the player's position. The class also includes a function to print/display the board on the terminal.

GameManager handles the logic of playing the game with the player's help of the GameBoard and gameState. The class includes functions such as runLoops that runs two while loops for playing the game, changeBoardSize that changes the difficulty level of the game, and playTurn and takeInput for playing a turn.

By using OOP concepts and implementing a stack-based algorithm, the codebase is modular, easy-to-understand, and efficient. 

## Challenges and Solutions

One of the biggest challenges I faced was implementing the stack-based algorithm to do the adjacent cell search. This involved understanding the data structures and algorithms required to implement the search in a way that is both efficient and accurate. I eventually solved this issue by breaking down the algorithm into smaller sub-problems and testing each one individually.

## Future Improvements

- Internally flatten the two-dimensional vector into a one-dimensional vector
- Add a flag system to mark suspected bomb locations
- Add a graphical user interface (GUI) to the game for a better user experience
- Incorporate additional sound effects to make the game more immersive
