#ifndef CELL_H
#define CELL_H

// game board's cell colors
typedef enum {gray, white, black, red} colors;
// game board's cell mine, otherwise number of mines in surrounding cells
typedef enum {yes=-1, no=0} mines;

// 2D array row_max x col_max of cell struct defines the playing board
typedef struct cell{
   colors color;
   mines mine;
}cell;

#endif
