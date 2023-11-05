#include "stdio.h"
#include "stdlib.h"

void main(){
  FILE* fp = NULL;
  fp=fopen("board6.txt","r");
  int row;
  int col;
  fscanf(fp,"%d %d",&row,&col);
  int i;
  int j;
  int* x;
  for (i=0; i<row; i++){
    for (j=0; j<col; j++){
      fscanf(fp, "%d", x);
    }
  }
}
