// #include all necessary .h files here.
#include "board.h"
#include "stdio.h"
#include "stdlib.h"
#include "minesweep.h"
#include "cell.h"

game* load_board(char* tBoard){

  //creates game object
  game* mine = (game*)malloc(sizeof(game));
  
  //opens file with name tBoard and checks if file exists
  int diff;
  while (1==1){
    
    scanf("Easy or hard game? (0 for easy | 1 for hard) %d\n", &diff);

    if(diff==0){
      mine->row_max = 10+1;
      mine->col_max = 10+1;
      break;
    }
    if(diff==1){
      mine->row_max = 15+1;
      mine->col_max = 15+1;
      break;
    }
    printf("Please insert 0 or 1\n");
  }

  //allocate space for cells
  mine->cells= malloc(sizeof(cell*)*mine->row_max);
  int i;
  for (i=0;i<mine->row_max;i++){
    mine->cells[i]= malloc(sizeof(cell)*mine->col_max);
  }
  //fill double array with cells
  mine->cells[1][1].color=red;
  mine->cells[1][1].mine=0;
  for (i=1;i<mine->col_max;i++){
    mine->cells[i][1].color=red;
    mine->cells[i][1].mine=i;
    mine->cells[1][i].color=red;
    mine->cells[1][i].mine=i;
  }
  //17% for hard mode and 10% for easy mode
  double density = 10+(7*diff);
  int j;
  for (i=1;i<mine->col_max;i++){
      for(j=1;j<mine->col_max;j++){
	double x = rand() % 100;
	if(x<=density){
	  mine->cells[i][j].mine=-1;
	}
      }
  }
  for (i=1;i<mine->col_max;i++){
      for(j=1;j<mine->col_max;j++){
	if(mine->cells[i][j].mine!=-1){
	  int x = 0;
	  if(mine->cells[i+1][j+1].mine==-1) x+=1;
	  if(mine->cells[i+1][j-1].mine==-1) x+=1;
	  if(mine->cells[i+1][j].mine==-1) x+=1;
	  if(mine->cells[i-1][j+1].mine==-1) x+=1;
	  if(mine->cells[i-1][j-1].mine==-1) x+=1;
	  if(mine->cells[i-1][j].mine==-1) x+=1;
	  if(mine->cells[i][j+1].mine==-1) x+=1;
	  if(mine->cells[i][j-1].mine==-1) x+=1;
	  mine->cells[i][j].mine=x;
	}
      }
  }
  
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
                printf("%d    ", board->cells[i][j].mine);
	    else if (board->cells[i][j].color == red)
	      printf("%d    ", board->cells[i][j].mine);
            else if (board->cells[i][j].color == white)
                printf("0    ");
            else if (board->cells[i][j].color == black)
                printf("B    ");
            else 
                printf("E    ");
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
    //}
}
