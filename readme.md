# Tic-Tac-Toe

Welcome to the Tic-Tac-Toe game! This project implements a console-based Tic-Tac-Toe game that ensures an optimal solution for the computer player, making it a challenging and fun game to play.

## How to Run

1. **Clone the Repository**:
    ```sh
    git clone https://github.com/yourusername/tic-tac-toe.git
    cd tic-tac-toe
    ```

2. **Compile the Code**:
    Ensure you have a C++ compiler installed. You can use `g++` (GNU Compiler Collection) to compile the code:
    ```sh
    g++ tic-tac-toe.cpp -o tic-tac-toe
    ```

3. **Run the Game**:
    ```sh
    ./tic-tac-toe
    ```

## How to Play

1. **Starting the Game**:
    When you run the game, the Tic-Tac-Toe board will be displayed. The board is a 3x3 grid with cells indexed as follows:

    ```
      0   1   2
    0 * | * | *
      -----------
    1 * | * | *
      -----------
    2 * | * | *
    ```

2. **Player Move**:
    - The player plays as 'X'.
    - You will be prompted to enter the coordinates of your move in the format `x y`.
    - For example, entering `1 1` will place an 'X' in the center of the board.

3. **Computer Move**:
    - The computer plays as 'O'.
    - The computer will make its move after you enter yours. The computer uses an optimal strategy to ensure it makes the best possible move.

4. **Winning the Game**:
    - The game will notify you if you win, lose, or if the game ends in a tie.
    - The game checks for winning conditions after each move.

## Optimal Solution

The computer player is programmed to make optimal moves using a strategy that includes:
- Blocking the player's winning moves.
- Creating and blocking potential L-formations.
- Making strategic first moves in the corners or center.
- Ensuring it makes the best possible move to either win or block the player.

## Code Structure

The main components of the code are:
- **Game Board Representation**: A 3x3 matrix to represent the Tic-Tac-Toe board.
- **Move Validation**: Checks to ensure moves are valid.
- **Winning and Tie Conditions**: Functions to check if the game has been won or if it ends in a tie.
- **Optimal Move Algorithm**: Logic to determine the computer's optimal move.

