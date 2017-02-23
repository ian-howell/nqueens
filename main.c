#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>

typedef struct Grid Grid;
struct Grid
{
  size_t size;
  char** grid;
};

Grid* create_grid(const unsigned int size);
void print_grid(const Grid* grid);
void delete_grid(Grid* grid);
int n_queens(Grid* board, const unsigned int current_queen);
int is_valid(Grid* board, const unsigned int row, const unsigned int col);

int main(int argc, char** argv)
{
  int size = 8;
  if (argc == 2)
    sscanf(argv[1], "%d", &size);
  printf("%d\n", size);

  Grid* board = create_grid(size);
  n_queens(board, board->size);
  delete_grid(board);
  return 0;
}

Grid* create_grid(const unsigned int size)
{
  Grid *new_grid = malloc(sizeof(Grid));
  new_grid->size = size;
  new_grid->grid = malloc(size * sizeof(char*));
  unsigned int i, j;
  for (i = 0; i < size; i++)
  {
    new_grid->grid[i] = malloc(size * sizeof(char));
    for (j = 0; j < size; j++)
    {
      if ((i + j) % 2)
        new_grid->grid[i][j] = '0';
      else
        new_grid->grid[i][j] = 'X';
    }
  }
  return new_grid;
}

void print_grid(const Grid* grid)
{
  unsigned int i, j;
  for (i = 0; i < grid->size; i++)
  {
    for (j = 0; j < grid->size; j++)
      printf("%c", grid->grid[i][j]);
    printf("\n");
  }
  return;
}

void delete_grid(Grid* grid)
{
  if (grid != NULL)
  {
    if (grid->grid != NULL)
    {
      unsigned int i;
      for (i = 0; i < grid->size; i++)
      {
        if (grid->grid[i] != NULL)
        {
          free(grid->grid[i]);
          grid->grid[i] = NULL;
        }
      }
      free(grid->grid);
    }
    free(grid);
  }
  return;
}

int n_queens(Grid* board, const unsigned int current_queen)
{
  if (current_queen == 0) // success!
    return 1;

  unsigned int i;
  for (i = 0; i < board->size; i++)
  {
    unsigned int row = board->size - current_queen;
    // Place a queen
    board->grid[row][i] = 'Q';
    print_grid(board);
    printf("\n");
    usleep(50000);

    // Check if that queen breaks any of the other queens
    if (!is_valid(board, row, i))
    {
      if ((row + i) % 2)
        board->grid[row][i] = '0';
      else
        board->grid[row][i] = 'X';

      print_grid(board);
      printf("\n");
      usleep(50000);
    }
    else
    {
      if (n_queens(board, current_queen-1))
      {
        return 1;
      }
      else
      {
        if ((row + i) % 2)
          board->grid[row][i] = '0';
        else
          board->grid[row][i] = 'X';

        print_grid(board);
        printf("\n");
        usleep(50000);
      }
    }
  }
  return 0;
}

int is_valid(Grid* board, const unsigned int row, const unsigned int col)
{
  unsigned int i;
  // check column
  for (i = 0; i < row; i++)
  {
    unsigned int delta = row - i;
    if (board->grid[i][col] == 'Q')
      return 0;
    if ((col + delta < board->size) && (board->grid[i][col + delta] == 'Q'))
      return 0;
    if (((int)(col - delta) >= 0) && (board->grid[i][col - delta] == 'Q'))
      return 0;
  }
  return 1;
}
