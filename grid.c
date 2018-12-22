#include <ncurses.h>

#include "grid.h"

Grid* create_grid(const unsigned int size)
{
    Grid *new_grid = malloc(sizeof(Grid));
    new_grid->size = size;
    new_grid->grid = malloc(size * sizeof(char*));
    for (unsigned int i = 0; i < size; i++) {
        new_grid->grid[i] = malloc(size * sizeof(char));
        for (unsigned int j = 0; j < size; j++) {
            if ((i + j) % 2) {
                new_grid->grid[i][j] = '0';
            } else {
                new_grid->grid[i][j] = 'X';
            }
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
        {
            if (grid->grid[i][j] == '0') {
                attron(COLOR_PAIR(1));
            } else if (grid->grid[i][j] == 'X') {
                attron(COLOR_PAIR(2));
            } else if (grid->grid[i][j] == 'Q') {
                if ((i + j) % 2) {
                    attron(COLOR_PAIR(3));
                } else {
                    attron(COLOR_PAIR(4));
                }
            }
            mvwprintw(stdscr, i, j, "%c", grid->grid[i][j]);
        }
    }
    refresh();
    return;
}

void delete_grid(Grid* grid)
{
    if (!grid) {
        return;
    }

    if (!grid->grid) {
        free(grid);
        return;
    }

    for (unsigned int i = 0; i < grid->size; i++) {
        if (grid->grid[i]) {
            free(grid->grid[i]);
            grid->grid[i] = NULL;
        }
    }
    free(grid->grid);
    return;
}

