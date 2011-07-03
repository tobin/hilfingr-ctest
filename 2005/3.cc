#include "contest.h"

#define D if (0)

int *make_puzzle() {
  return (int *)calloc(9 * 9, sizeof(int));
}

void print_puzzle(int *puzzle) {
  for (int i=0; i<81; i++) {
    printf("%d%c", puzzle[i], i%9==8 ? '\n' : ' ');
  }
}

int get_pos(int *puzzle, int x, int y) {
 return puzzle[9*x + y];
}

int check_puzzle(int *puzzle) {
  for (int row=0; row<9; row++) {
    int check[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i=0; i<9; i++) {
      int val = get_pos(puzzle, row, i);
      check[val] ++;
      if (check[val] > 1 && val>0) {
        D printf("check-row failed in row %d, col %d.\n", row, i);
        return 0;
      }
    }
  }

  for (int col=0; col<9; col++) {
    int check[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i=0; i<9; i++) {
      int val = get_pos(puzzle,i, col);
      if (((++check[val]) > 1) && val>0) {
        D printf("check-col failed.\n");
        return 0;
      }
    }
  }

  for (int qx=0; qx<3; qx++) 
    for (int qy=0; qy<3; qy++) {
      // check the quadrant starting at qx, qy
      //      D printf("checking quadrant starting at %d, %d\n", 3*qx, 3*qy);
      int check[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
      for (int x=0; x<3; x++)
        for (int y=0; y<3; y++) {
	  //	  D printf("examining row %d col %d\n", (3*qx)+x, (3*qy)+y);
          int val = get_pos(puzzle, (3*qx)+x,(3*qy)+y);
          if (((++check[val]) > 1) && val>0) {
            D printf("check-quadrant failed\n");
            return 0;
          }
        }
  }
  return 1;
}

int solve(int *puzzle, int pos) {
  D printf("Trying to solve at position %d\n", pos);
  if (pos==81)
    return 1; // success!

  if (puzzle[pos]!=0)  // this position is already bound
    return (solve(puzzle, pos+1));

  for (int t=1; t < 10; t++) {
    puzzle[pos] = t;
    D printf("trying position %d with value %d\n", pos, t);
    if (!check_puzzle(puzzle)) continue;
    D printf("bound position %d to value %d\n", pos, t);
    //    print_puzzle(puzzle);
    if (solve(puzzle, pos+1) == 1) return 1; // success
  }
  puzzle[pos] = 0; 
  return 0;
}

int main(void) {
  int *puzzle = make_puzzle(); 
  for (int i=0; i<81; i++)
    scanf("%d",&(puzzle[i])); 
  //  print_puzzle(puzzle);
  if (solve(puzzle, 0)) 
    print_puzzle(puzzle);
  else
    printf("There was no solution.");
  free(puzzle);
  return 0;
}
