#ifndef MINESWEEP_H
#define MINESWEEP_H

#include "cell.h"
#include "stdio.h"
#include "stdlib.h"

// game board struct -- height/width defined as row_max col_max
// cells is 2D array of  
typedef struct game {
  int row_max;
  int col_max;
  cell** cells;
} game;

/* function prototypes */
void free_board(game*);
int play_game(char*);
int process_click(game*, int, int, int);
int uncover(game*, int, int);
int check_game(game*);

#endif
