#include "stdio.h"
#include "stdlib.h"
#include "cell.h"
#include "board.h"
#include "minesweep.h"
// #include all necessary .h files here

/* play_game
* args: f_name -- unchecked file name that contains board cofiguration
* out: int return game status if needed for the best score keeping
* creates the game instance
*  reads command line for click's x/y and click type (forever unless otherwise specified):
*  Enter row in range 1-board height: enter column range 1-board width click type(0: unvover 1: mine)
*  Example= 1:3 0 -- row=1 col=3 try uncover
*  Example= 2:1 1 -- row=2 col=1 mark as a mine
*  Enter '-1' to check if game is won and quit the game
*
*  call process_click with x/y and a move type
*  check the process_click return for the game result 
*/
int play_game(char* f_name){
    game* board = load_board(f_name);
    if(board == NULL){
        fprintf(stderr, "ERROR: Cound not allocate board or read from file\n");
        return EXIT_FAILURE;
    }
    int ret, r, c, m = 0;
    while(1){
        print_board(board);
        printf("Enter row(1-%d):column(1-%d) and click type(0: unvover 1: mark a mine)\n", board->row_max, board->col_max);
        printf("Example= 1:3 0 -- row=1 col=3 try uncover\n");
        printf("Example= 2:1 1 -- row=2 col=1 mark as a mine\n");
        printf("Enter '-1' to quit the game \n");

        scanf("%d:%d%d", &r, &c, &m);
        if(r==-1 || c==-1 || m==-1){
            if(check_game(board))
                printf("CONGRATS YOU WON!!!\n");    
            else
                printf("YOU LOST -- GAME OVER -- mines mis-identified\n");    
            break;
        }else if(r<1 || c<1 || r > board->row_max || c > board->col_max || m < 0 || m > 1)
            printf("Illegal move or click type, try again!\n");
        else{
            ret = process_click(board, --r, --c, m);
            if (ret == 0){
                printf("GAME OVER, you stepped on a mine or marked it as a mine\n");
                break;
            }else
                printf("Good one, keep on clicking\n");
        }

    }
    printf("Thank you for playing\n");
    free_board(board);
    return EXIT_SUCCESS;
}

//frees all mallocs
void free_board(game* gme){
  int i;
  for (i=0;i<gme->row_max;i++){
    free(gme->cells[i]);
  }
  free(gme->cells);
  
}

int process_click(game* gme, int row, int col, int click){

  //toggles between flagged and unflagged
  if (click==1) {
    if (gme->cells[row][col].color==black){
      gme->cells[row][col].color=gray;
    } else if (gme->cells[row][col].color==gray) {
      gme->cells[row][col].color=black;
    }else{
      printf("cell has already been uncovered\n");
    }
    return 1;
  }
  //returns 1 if cell is already uncovered or if flagged
  if(gme->cells[row][col].color==black || gme->cells[row][col].color==white){
    return 1;
  }
  //ends game if bomb
  //otherwise uncovers cell and calls uncover if mine = 0
  if(gme->cells[row][col].color==gray){
    if (gme->cells[row][col].mine<0){
      return 0;
    }
    
    if (gme->cells[row][col].mine>0){
      gme->cells[row][col].color=white;
      return 1;
    }
  }
  uncover(gme, row, col);
  return 1;
}

int uncover(game* gme, int row, int col){

  //break recursion if out of bounds or if already uncovered or flagged
  if (row<0 || col<0 || row>gme->row_max-1 || col>gme->col_max-1) return 1;
  if (gme->cells[row][col].color != gray) return 1;

  //uncovers cell and checks if next to a bomb
  gme->cells[row][col].color = white;
  if (gme->cells[row][col].mine>0) return 1;

  //calls function on all squares around
  uncover(gme, row+1,col+1);
  uncover(gme, row+1,col);
  uncover(gme, row+1,col-1);
  uncover(gme, row,col+1);
  uncover(gme, row,col-1);
  uncover(gme, row-1,col+1);
  uncover(gme, row-1,col);
  uncover(gme, row-1,col-1);
  return 1;
  
}

int check_game(game* gme){
  //checks if the game is won
  //only bombs are left grey or black
  //nothing else is gray or black
  int r, c;
  for (r=0;r<gme->row_max;r++){
    for (c=0;c<gme->col_max;c++){
      if ((gme->cells[r][c].color==gray||gme->cells[r][c].color==black)
	  && gme->cells[r][c].mine>-1) return 0;
    }
  }
  return 1;
}
