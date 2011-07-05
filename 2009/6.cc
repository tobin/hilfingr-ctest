#include "contest.h"
#include <assert.h>

int N;
int grid[10][10];

#define D if (0)

int error_found() {
  for (int r=1; r<N+1; r++) {
    for (int c=1; c<N+1; c++) {
      // check whether any neighbor is unassigned
      int fully_assigned = !(grid[r][c]==-1 || grid[r][c+1]==-1 || grid[r][c-1]==-1 || grid[r+1][c]==-1 || grid[r-1][c]==-1);
      if (!fully_assigned) 
	continue;
      if (grid[r][c] != ((grid[r][c+1] + grid[r][c-1] + grid[r+1][c] + grid[r-1][c]) % 3))
	return 1; // condition not met
    }
  }
  return 0; // no errors found
}

int solve(int x, int N) {
  int row = (x / N);
  int col = x - row*N;
  
  D printf("solve(%d = (%d, %d))\n", x, row+1, col+1);
  assert(row>=0);
  assert(col>=0);

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

  // no errors, not done
  for (int choice=0; choice<3; choice ++) {
    D printf("choosing grid[%d][%d]==%d\n", row+1, col+1, choice);
    grid[row+1][col+1] = choice;
    if (solve(x+1, N))
      return 1;
  }
  D printf("unsetting grid[%d][%d]\n", row+1, col+1);
  grid[row+1][col+1] = -1;
  return 0;
}


void print_grid() {
  printf("   ");
  for (int c=1; c<=N; c++)
    printf(" %d", grid[0][c]);
  printf("\n");
  for (int i=0; i<(7+2*N); i++) printf("-");
  printf("\n");
  for (int r=1; r<=N; r++){
    printf("%d |", grid[r][0]);
    for (int c=1; c<=N; c++)
      printf(" %d", grid[r][c]);
    printf(" | %d", grid[r][N+1]);
    printf("\n");
  }
  for (int i=0; i<(7+2*N); i++) printf("-");
  printf("\n");
  printf("   ");
  for (int c=1; c<=N; c++)
    printf(" %d", grid[N+1][c]);
  printf("\n");
}

int main(int argc, char **argv) {
  int G = 0;
  while (1==scanf("%d", &N) && N>0) {
    G++;
    printf("Lock %d:\n", G);
    D printf("Grid size N=%d\n", N);
    // get the carved numbers
    D printf("Loading carved numbers\n");
    for (int c=1; c<N+1; c++) scanf("%d", &(grid[0][c]));   // across the top
    for (int r=1; r<N+1; r++) scanf("%d", &(grid[r][N+1])); // down the right
    for (int c=1; c<N+1; c++) scanf("%d", &(grid[N+1][c])); // across the bottom
    for (int r=1; r<N+1; r++) scanf("%d", &(grid[r][0]));   // down the left

    D printf("Initializing the grid\n");
    // initialize the inner grid
    for (int r=1; r<N+1; r++)
      for (int c=1; c<N+1; c++)
	grid[r][c] = -1; // unassigned

    D printf("Here's the grid:\n");    
    D print_grid();

    D printf("Solving...\n");
    if (solve(0,N)) {
      D printf("Solved!\n");
    } else {
      D printf("Could not solve\n");
    }

    D printf("Here's the grid:\n");    
    print_grid();
  }
  return 0;
}
