#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <ncurses.h>
//#define show_errors

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
void flash_error(unsigned int row, unsigned int col);

int DELAY = 500000;

int main(int argc, char** argv)
{
    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_WHITE);
    init_pair(5, COLOR_RED  , COLOR_BLACK);
    init_pair(6, COLOR_GREEN, COLOR_RED  );
    curs_set(0);

    int size = 8;
    if (argc >= 2) {
        sscanf(argv[1], "%d", &size);
    }
    if (argc >= 3) {
        sscanf(argv[2], "%d", &DELAY);
    }

    Grid* board = create_grid(size);
    if (n_queens(board, board->size)) {
        attron(COLOR_PAIR(3));
        mvwprintw(stdscr, board->size, 0, "Success!");
    } else {
        attron(COLOR_PAIR(5));
        mvwprintw(stdscr, board->size, 0, "Failure...");
    }

    delete_grid(board);
    getch();
    endwin();
    return 0;
}

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

int n_queens(Grid* board, const unsigned int current_queen)
{
    if (current_queen == 0) { // success!
        return 1;
    }

    for (unsigned int i = 0; i < board->size; i++) {
        unsigned int row = board->size - current_queen;
        // Place a queen
        board->grid[row][i] = 'Q';
        print_grid(board);
        usleep(DELAY);

        // Check if that queen breaks any of the other queens
        if (!is_valid(board, row, i)) {
            if ((row + i) % 2) {
                board->grid[row][i] = '0';
            } else {
                board->grid[row][i] = 'X';
            }
        } else {
            if (n_queens(board, current_queen-1)) {
                return 1;
            } else {
                if ((row + i) % 2) {
                    board->grid[row][i] = '0';
                } else {
                    board->grid[row][i] = 'X';
                }
            }
        }
    }
    return 0;
}

int is_valid(Grid* board, const unsigned int row, const unsigned int col)
{
    // check column
    for (unsigned int i = 0; i < row; i++) {
        unsigned int delta = row - i;
        if (board->grid[i][col] == 'Q') {
            flash_error(i, col);
            return 0;
        }

        if ((col + delta < board->size) && (board->grid[i][col + delta] == 'Q')) {
            flash_error(i, col + delta);
            return 0;
        }

        if (((col - delta) >= 0u) && (board->grid[i][col - delta] == 'Q')) {
            flash_error(i, col - delta);
            return 0;
        }
    }
    return 1;
}

void flash_error(unsigned int row, unsigned int col)
{
#ifdef show_errors
    attron(COLOR_PAIR(6));
    mvwprintw(stdscr, row, col, "Q");
    refresh();
    usleep(DELAY * 5);
#endif
}
