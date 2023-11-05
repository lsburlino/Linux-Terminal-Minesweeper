// #include all necessary .h files here.
#include "board.h"
#include "stdio.h"
#include "stdlib.h"
#include "minesweep.h"
#include "cell.h"
//declaration for later
int value_check (game* gme, int row, int col);

//creates game object if board dimensiions match board size in file.
//otherwise returns null
game* load_board(char* tBoard){

  //creates game object
  game* mine = (game*)malloc(sizeof(game));
  
  //opens file with name tBoard and checks if file exists
  FILE* fp = NULL;
  fp=fopen(tBoard,"r");
  if (fp == NULL){
    printf("No board found");
    return NULL;
  }


  //inputs the board size and checks to see if it is valid
  fscanf(fp,"%d %d",&mine->row_max,&mine->col_max);
  if (mine->row_max<3 || mine->col_max<3) return NULL;

    //got from w3resource.com/c-programming-exercises/file-handling/c-file-handling-excercise-5.php

  //checks characters to see if there is the right amount of numbers in the
  //array and if they are correctly in columns
  char c;
  int x =0;
  int l_counter=0;
  int n_counter=0;
  for (c=getc(fp);c != EOF; c = getc(fp)){

    if(c== '\n'){
      l_counter++;
      if (x%mine->col_max!=0 && l_counter>1)
	return NULL;
      x=0;
    }
      if(c>='0'&&c<='9'&&l_counter>0) {
	n_counter++;
	x++;
      }
  }
  if ((mine->row_max*mine->col_max)!=n_counter)
    return NULL;

  //allocate space for cells
  mine->cells= malloc(sizeof(cell*)*mine->row_max);
  int i;
  for (i=0;i<mine->row_max;i++){
    mine->cells[i]= malloc(sizeof(cell)*mine->col_max);
  }
  //sets index of scanner to right value
  rewind(fp);
  mine->row_max=0;
  mine->col_max=0;
  fscanf(fp,"%d %d",&mine->row_max,&mine->col_max);

  //fill double array with cells
  int j;
  for (i=0;i<mine->row_max;i++){
    for (j=0;j<mine->col_max;j++){
      mine->cells[i][j].color=gray;
      fscanf(fp, "%d", &mine->cells[i][j].mine);
    }
  }

  //checks to see if values in array are right
  for (i=0;i<mine->row_max;i++){
    for (j=0;j<mine->col_max;j++){
      if(mine->cells[i][j].mine!=-1){
	if(mine->cells[i][j].mine<-1) return NULL;
	int x = 0;
	//top left corner
	x += value_check(mine, i+1, j+1);
	x += value_check(mine, i, j+1);
	x += value_check(mine, i-1, j+1);
	x += value_check(mine, i+1, j-1);
	x += value_check(mine, i, j-1);
	x += value_check(mine, i-1, j-1);
	x += value_check(mine, i-1, j);
	x += value_check(mine, i+1, j);

	if (x!=mine->cells[i][j].mine) return NULL;
      }
    }
  }
	  
    
  

  fclose(fp);
  
  return mine;
  
  
}

/* print_game 
* args: pointer to the current board struct
* out: void
* prints the game board: 
    if cell color is white and number of mines is >0, print mine count otherwise
    if cell is white, print the mine count 0 otherwise
    if cell color is black 'B', print B otherwise, 
    if cell color is gray 'E'
*/
void print_board(game* board){
    printf("Board colors %d x %d\n", board->row_max, board->col_max);
    for(int i=0; i< board->row_max; i++){
        for(int j=0; j < board->col_max; j++){
            if(board->cells[i][j].color == white && board->cells[i][j].mine >0)
                printf("%d\t", board->cells[i][j].mine);
            else if (board->cells[i][j].color == white)
                printf("0\t");
            else if (board->cells[i][j].color == black)
                printf("B\t");
            else 
                printf("E\t");
        }
        printf("\n");
    }
    // uncommnet this to print the board again showing the mine locations
    //printf("Mines on the Board (-1: mine, 1: otherwise): %d x %d\n", board->row_max, board->col_max);
    //for(int i=0; i< board->row_max; i++){
    //    for(int j=0; j < board->col_max; j++){
    //       printf("%d\t", board->cells[i][j].mine);
    //   }
    //  printf("\n");
    // }
}
//checks if a mine exists in a cell
 int value_check (game* gme, int row, int col){
   if (row<0 || col<0 || row>gme->row_max-1 || col>gme->col_max-1) return 0;
   if (gme->cells[row][col].mine<0) return 1;
   return 0;
 }
