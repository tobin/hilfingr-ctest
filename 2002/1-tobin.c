#include <contest.h>

char getboard(char *board,int x, int y) {  return board[x*7 + y]; }
void setboard(char *board,int x, int y, char c) { board[x*7+y] = c; }
int inboard(int x, int y) {   return (x>=0) && (x<7) && (y>=0) && (y<7); }

char *copy_board(char *board) {
  return memcpy(calloc(7*7,sizeof(char)),board,7*7);
}

int score(char *board, char player) {
  int i;
  int s = 0;
  for (i=0; i<(7*7); i++)
    if (board[i]==player) s++;
  return s;
}

char *search(char *board, char me) {  // 0 = black, 1 = white
  int i, j, x, y, p, q;
  char *best_board = board;
  int best_score = -49;
  int this_score;

  // choose a piece to investigate
 
  for (x=0; x<7; x++)
    for (y=0; y<7; y++) {
      if (getboard(board,x,y) != me) continue;  // not my piece
      for (i=-2; i<=2; i++) 
	for (j=-2; j<=2; j++) {
	  char *new_board;
	  if (i==0 && j==0) continue;              
	  if (!inboard(x+i,y+j)) continue;        // not on the board
	  if (getboard(board,x+i,y+j) != '-') continue; // not empty
	  
	  new_board = copy_board(board);
	  
	  if ((abs(i) > 1) || (abs(j) > 1))   // this is an extension
	    setboard(new_board,x,y,'-');	  
	  setboard(new_board,x+i,y+j,me);

	  // claim the surrounding squares
	  
	  for (p=-1; p<=1; p++) 
	    for (q=-1; q<=1; q++) {
	      if (inboard(x+i+p,y+j+q) && 
		  (getboard(new_board,x+i+p,y+j+q) != '-'))
		setboard(new_board,x+i+p,y+j+q,me);
	    }
	  
	  if (me == 'b')
	    this_score = score(search(new_board,'w'),'b');
	  else
	    this_score = 50 - score(new_board,'b');
	  
	  if (this_score > best_score) {
	    best_score = this_score;
	    best_board = new_board;
	  }
	}
    }
  return best_board;
}

int main(void) {
  char board[7][7];
  int i, j, k, b=0;
  char *boards[2];
  boards[0] = board;
  while (1) {
    for (i=0; i<7; i++) 
      if (1 != scanf("%s",board[i])) return 0;
    board[1] = search(board[0],'b');
    printf("Board %d.\n",++b);
    for (i=0; i<7; i++) { 
      for (k=0; k<2; k++) {
	for (j=0; j<7; j++)  
	  printf("%c",getboard(boards[k],i,j));
	printf("        ");
      }
      printf("\n");
    }
    printf("\n");
  }
  return 0;
}
