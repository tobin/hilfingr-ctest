#include "contest.h"
#include <assert.h>

int N;
int grid[12][12];
int crossed[12][12];  // 0 = not crossed out, 1 = crossed out, -1 = undecided

#define D if (0)

int one_piece() {
    int reachable[12][12];
  for (int i=0; i<N+2; i++)
    for (int j=0; j<N+2; j++)
      reachable[i][j] = 0;

  // find an uncrossed square to set
  int uncrossed_found = 0;
  for (int r=1; r<N+1; r++)
    for (int c=1; c<N+1; c++) {
      if (crossed[r][c]==0) {
	uncrossed_found = 1;
	reachable[r][c] = 1;
	break;
      }
    }
  
  if (!uncrossed_found)
    return 1;
  
  // floodfill
  for (int iteration=0; iteration<100; iteration++) {
    for (int r=1; r<N+1; r++)
      for (int c=1; c<N+1; c++) {
	if (crossed[r][c]==1)
	  continue;
	// if this square is uncrossed, it can reach any of its (uncrossed) neighbors
	reachable[r][c] |= (crossed[r][c+1]!=1 && reachable[r][c+1]);
	reachable[r][c] |= (crossed[r][c-1]!=1 && reachable[r][c-1]);
	reachable[r][c] |= (crossed[r+1][c]!=1 && reachable[r+1][c]);
	reachable[r][c] |= (crossed[r-1][c]!=1 && reachable[r-1][c]);
      }
  }
  
  int any_unreachable = 0;
  for (int r=1; r<N+1; r++)
    for (int c=1; c<N+1; c++) 
      if (crossed[r][c]!=1  && !reachable[r][c])
	any_unreachable = 1;
  
  return !any_unreachable;     
}

int error_found() {
  int occurs_row[102];
  int occurs_col[102];

  
  // check for adjacent crossings
  for (int r=1; r<N+1; r++) 
    for (int c=1; c<N+1; c++) 
      if (crossed[r][c]==1) {
	if (crossed[r][c+1]==1 || crossed[r][c-1]==1 || crossed[r+1][c]==1 || crossed[r-1][c]==1)
	  return 1;
      }

  // search row and column j
  for (int j=1; j<N+1; j++) {
    // initialize
    for (int i=0; i<100; i++) {
      occurs_row[i] = 0;
      occurs_col[i] = 0;
    }

    for (int i=1; i<N+1; i++) {
      if (crossed[i][j]==0) {
	if (occurs_row[grid[i][j]])
	  return 1;
	occurs_row[grid[i][j]] = 1;
      }

      if (crossed[j][i]==0) {
	if (occurs_col[grid[j][i]]) 
	  return 1;
	occurs_col[grid[j][i]] = 1;
      }
    }
  }

  if (!one_piece())
    return 1;

  return 0; // no errors found
}

int solve(int x, int N, int depth) {
  int row = (x / N) + 1;
  int col = x - (row - 1)*N + 1;
  
  D printf("solve(%d = (%d, %d))\n", x, row, col);
  assert(row>0);
  assert(col>0);

  // if there's an error -- backtrack
  if (error_found()) {
    D printf("Error found - backtracking\n");
    return 0;
  }

  // if we've set all the puzzle elements with no errors, we're done
  if (x > N*N) {
    D printf("Solution found!");
    return 1;
  }

  // if there are still errors but we've used up all our crosses, there's no solution
  if (depth==0)
    return 0;

  // no errors, not done
  for (int choice=0; choice<2; choice ++) {
    D printf("choosing crossed[%d][%d]==%d\n", row, col, choice);
    crossed[row][col] = choice;
    if (solve(x+1, N, choice ? (depth-1) : (depth)))
      return 1;
  }
  D printf("unsetting crossed[%d][%d]\n", row, col);
  crossed[row][col] = -1;
  return 0;
}


void print_board() {
  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
      printf(" %c%d%c", 
	     crossed[i+1][j+1]==1 ? '(' : ' ', grid[i+1][j+1],
	     crossed[i+1][j+1]==1 ? ')' : ' ' );
    }
    printf("\n");
  }
}

void initialize() {
  for (int i=0; i<=N+1; i++) {
    crossed[0][i]   = 0;
    crossed[N+1][i] = 0;
    crossed[i][0]   = 0;
    crossed[i][N+1] = 0;
  }
  for (int i=0; i<N; i++)
    for (int j=0; j<N; j++) 
      crossed[i+1][j+1] = -1; // undecided    
}

int do_solve() {
  int solved = 0;
  for (int depth=0; depth<(N*N); depth++) {
    D printf("Initiating search at depth %d\n", depth);
    initialize();
    if (solve(0, N, depth)) {
      solved = 1;
      break;
    }
  }
  return solved;
}

int main(int argc, char **argv) {

  int G = 0;
  while (1 == scanf("%d", &N) && N>0) {
    G ++;
    printf("Grid %d:\n", G);
    
    for (int i=0; i<N; i++)
      for (int j=0; j<N; j++) 
	scanf("%d", &(grid[i+1][j+1]));
	
    if (do_solve()) {
      D printf("Solved!\n");
    } else 
      printf("NOT SOLVED\n");
    
    print_board();
    
  }
  return 0;
}

