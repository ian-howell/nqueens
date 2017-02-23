#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct Grid Grid;
struct Grid
{
  size_t size;
  char** grid;
};

Grid* create_grid(const unsigned int size);
void print_grid(const Grid* grid);
void delete_grid(Grid* grid);

int main(int argc, char** argv)
{
  int size = 8;
  if (argc == 2)
    sscanf(argv[1], "%d", &size);
  printf("%d\n", size);

  Grid* board = create_grid(size);
  print_grid(board);
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
