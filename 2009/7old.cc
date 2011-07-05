#include "contest.h"
#include <assert.h>

k

#define D if (1)

int solve(int depth) {
  // breadth-first search

  D printf("Solving at depth %d\n", depth);
  int solved = 1;

  // scan each row and column to find a candidate to cross out

	D printf("Duplicate '%d' found at %d, %d\n", grid[i][j], i, j);
	// check whether we're allowed to cross any more out
	if (depth == 0) {
	  D printf("Found duplicate at depth 0 - backtracking\n");
	  return 0;
	}

	// Check whether we're allowed to cross this one out
	if (crossed[i+1][j] || crossed[i-1][j] || crossed[i][j-1] || crossed[i][j+1]) {
	  // one of the neighbors is crossed out already
	  continue;
	}

	// Try crossing out this position
	D printf("crossing out at %d, %d\n", i, j);
	crossed[i][j] = 1;
	if (solve(depth - 1))
	  return 1;
	// uncross it
	crossed[i][j] = 0;
      }
      occurs_row[grid[i][j]] = 1;
    }
    
    // CHECK COLUMN J
     for (int i=1; i<N+1; i++) {
      // already crossed out - do nothing
      if (crossed[j][i])
	continue;
      
      if (occurs_col[grid[j][i]]) {
	D printf("Duplicate '%d' found at %d, %d\n", grid[j][i], j, i);
	// check whether we're allowed to cross any more out
	if (depth == 0) {
	  D printf("Found duplicate at depth 0 - backtracking\n");
	  return 0;
	}

	// Check whether we're allowed to cross this one out
	if (crossed[i+1][j] || crossed[i-1][j] || crossed[i][j-1] || crossed[i][j+1]) {
	  // one of the neighbors is crossed out already
	  continue;
	}

	// Try crossing out this position
	D printf("crossing out at %d, %d\n", i, j);
	crossed[j][i] = 1;
	if (solve(depth - 1))
	  return 1;
	// uncross it
	crossed[j][i] = 0;
      }
      occurs_col[grid[j][i]] = 1;
    }
  }

  return (depth == 0);
}

