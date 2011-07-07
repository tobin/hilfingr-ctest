#include <stdio.h>
#include <stdlib.h>

/* Tobin Fricke (SID 13934220) (tobin@cory.eecs) (tobin@splorg.org)
   31 August 2001

   CS 198, assignment 1, problem 2
   (Berkeley Programming Contest 1998, problem 3)

   Estimated time:1 hour
   Actual time: 3 hours 

   The first difficulty was choosing a representation for the board that would be 
   easy to implement.  My first choice, a simple 24 element array, proved to be
   too confusing, so I changed to using a full 8x8 array directly representing
   the board as a human would.  This proved much easier to conceptualize.

   The implementation iterates through all black pieces and for each explores the
   tree of all possible capture paths.  At the end of a capture path, the same
   procedure is performed for white.  A second problem was how to return the 
   sequence of moves.  This information needs to be passed as a return value in
   addition to the score attained in a capture path.  If C had a simple stack
   or list type, or had less awkward provisions for complex return values,
   less debugging would have been required.  

   Bugs: malloc() without free()

*/

int board[8][8];
int n_black;
int n_white;

#define EMPTY 0
#define BLACK 1
#define WHITE 2

#define D if (0)

typedef struct _move_t {
  int row, col;
  struct _move_t *next;
} move_t;


void print_board() {
  int row,col;
  printf("  ");
  for (col=0; col<8; col++) 
    printf("%d",col);
  printf("\n");
  for (row=0; row<8; row++) {
    printf("%d ",row);
    for (col=0; col<8; col++) 
      printf("%c",(board[row][col] == EMPTY ? '.' :
		   (board[row][col] == WHITE ? 'w' : 
		    (board[row][col] == BLACK ? 'b' : 
		     '?'))));
    printf("\n");
  }
}

bool valid_cell(int row, int col) {
  return (row >= 0) && (row <= 7) && (col >= 0) && (col <= 7);
} 

bool can_capture(int me, int opponent, int origin_row, int origin_col, int capture_row, int capture_col, 
		 int target_row, int target_col) {
  
  return (valid_cell(origin_row,origin_col) && 
	  valid_cell(capture_row,capture_col) && 
	  valid_cell(target_row,target_col) &&
	  (board[origin_row][origin_col] == me) && 
	  (board[capture_row][capture_col] == opponent) &&
	  (board[target_row][target_col] == EMPTY));
}

int play(int me, int opponent, int row, int col, bool first_player, move_t **moves);

int test_capture(int me, int opponent, int origin_row, int origin_col, int capture_row, int capture_col, 
		 int target_row, int target_col, bool first_player, move_t **moves) {

  int score;

  /* perform the capture */
  board[target_row][target_col] = me;
  board[capture_row][capture_col] = EMPTY;
  board[origin_row][origin_col] = EMPTY;
  
  score = play(me, opponent, target_row, target_col, first_player, moves);
  
  /* put things back */
  board[target_row][target_col] = EMPTY;
  board[capture_row][capture_col] = opponent;
  board[origin_row][origin_col] = me;

  return score;
}


move_t *move_gen(int row, int col, move_t *next) {
  move_t *foo = (move_t *)calloc(sizeof(move_t),1);
  foo->row = row;
  foo->col = col;
  foo->next = next;
  return foo;
}


int find_best_move(int me, int opponent, bool first_player, move_t **moves);

int play(int me, int opponent, int row, int col, bool first_player, move_t **moves) {

  bool can_capture_right, can_capture_left;
  move_t *moves_right, *moves_left;
  int score_right = 0;
  int score_left = 0;

  if (me == BLACK) {
    D printf("BLACK: ");

    can_capture_left = can_capture(me,opponent,row,col,row+1,col+1,row+2,col+2);
    can_capture_right = can_capture(me,opponent,row,col,row+1,col-1,row+2,col-2);
   
    D printf(" From (%d,%d): Right? %s Left? %s\n",row,col,(can_capture_right ? "Yes" : "No"),
	   (can_capture_left ? "Yes" : "No"));

    if (can_capture_left)
      score_left = 1 + test_capture(me,opponent,row,col,row+1,col+1,row+2,col+2,first_player,&moves_left);
    if (can_capture_right)
      score_right = 1 + test_capture(me,opponent,row,col,row+1,col-1,row+2,col-2,first_player,&moves_right);

    moves_left = move_gen(row+2,col+2,moves_left);
    moves_right = move_gen(row+2,col-2,moves_right);

  } else {

    D printf("WHITE: ");

    can_capture_left = can_capture(me,opponent,row,col,row-1,col-1,row-2,col-2);
    can_capture_right = can_capture(me,opponent,row,col,row-1,col+1,row-2,col+2);

    if (can_capture_left)
      score_left = 1 + test_capture(me,opponent,row,col,row-1,col-1,row-2,col-2,first_player,&moves_left);
    if (can_capture_right)
      score_right = 1 + test_capture(me,opponent,row,col,row-1,col+1,row-2,col+2,first_player,&moves_right);
    
    moves_left = move_gen(row-2,col-2,moves_left);
    moves_right = move_gen(row-2,col+2,moves_right);
  }

  if ((!can_capture_right) && (!can_capture_left) && first_player) {
    move_t *temp_moves;
    *moves = NULL;
    D printf(" returning 0 (no captures available)\n");
    return - find_best_move(opponent,me,false,&temp_moves); 
  }  else {
    if ((can_capture_left && (!can_capture_right)) ||
	(can_capture_left && can_capture_right && (score_left > score_right))) {
      *moves = moves_left;
      D printf(" returning %d (score_left)\n",score_left);
      return score_left;
    } else {
      *moves = moves_right;
      D printf(" returning %d (score_right)\n",score_right);
      return score_right;
    }
  }
}

int find_best_move(int me, int opponent, bool first_player, move_t **moves) {
  int best_score, best_row, best_col;
  move_t *best_moves;
  bool first = true;
  for (int row=0; row<8; row++) 
    for (int col=0; col<8; col++) 
      if (board[row][col] == me) {
       	int score;
	move_t *move_list;
	D printf("Looking for the best moves starting from (%d,%d)\n",row,col);
	score = play(me,opponent,row,col,first_player,&move_list);
	D printf("The score from (%d,%d) was %d\n",row,col,score);
	if ((score > best_score) || first) {
	  D printf("This is the new best score.\n");
	  best_score = score;
	  best_row = row;
	  best_col = col;
	  best_moves = move_list;
	  first = false;
	}
      }
  D printf("Making the final move_gen()\n");
  *moves = move_gen(best_row,best_col,best_moves);
  return best_score;
}
      
    

int rowcoltolinear(int row, int col) {
  if (row%1 == 0) 
    col -= 1;
  col /= 2;
  return row*4+col+1;
}

int main(int argc, char **argv) {
  int temp,row,col;
  move_t *the_moves_list;

  scanf("%d",&n_black);
  for (int i=0; i<n_black; i++) {
    scanf("%d",&temp);
    row = (temp-1) / 4;
    col = 2*((temp-1) % 4)+((row+1)%2);
    board[row][col] = BLACK;
    D printf("Placing BLACK at %d (%d,%d)\n",temp,row,col);
  }
  
  scanf("%d",&n_white);
  for (int i=0; i<n_white; i++) {
    scanf("%d",&temp);
    row = (temp-1) / 4;
    col = 2*((temp-1) % 4)+((row+1)%2);
    board[row][col] = WHITE;
    D printf("Placing WHITE at %d (%d,%d)\n",temp,row,col);
  }

  temp = find_best_move(BLACK,WHITE,true,&the_moves_list);
  
  printf("Best move sequence is ");
  while (the_moves_list != NULL) {
    printf("%d",   rowcoltolinear(the_moves_list->row,the_moves_list->col));
    the_moves_list = the_moves_list ->next;
    if (the_moves_list) printf("-");
  }
  printf("\n");
  return 0;
}







