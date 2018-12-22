#ifndef GRID_H
#define GRID_H

#include <stdlib.h>

typedef struct Grid
{
  size_t size;
  char** grid;
} Grid;

Grid* create_grid(const unsigned int size);
void print_grid(const Grid* grid);
void delete_grid(Grid* grid);

#endif
