# nqueens
A graphical demonstration of the N Queens problem

The [N Queens Problem](https://en.wikipedia.org/wiki/Eight_queens_puzzle) is the problem of placing N
chess queens on an N×N chessboard so that no two queens threaten each other. This problem can be solved
using recursive backtracking. First, a queen is placed into its row. It then checks that it is not threatened
by any of the other queens. If it is threatened, it moves to the next step. If it is found that there is no
valid move in that row, the algorithm steps back and tries a new position for the prior queen. The algorithm
progresses until either all N queens all safely placed on the board or when there are no more valid moves.
