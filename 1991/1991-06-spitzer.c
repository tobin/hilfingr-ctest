/* Determines the number of step need to reach the exit of a 2d maze
 * By: Chris Spitzer
 */

#include <stdlib.h>
#include <stdio.h>

/* with 1 unit padding */
#define MAXX 82
#define MAXY 82

char maze[MAXY][MAXX];
int stat[MAXY][MAXX];
/*Diagonal search: */
/*int srch[] = {-1, -1, 1, 1};*/
/*Horiz/vert search: */
int srch[] = {-1, 0, 1, 0};
int nx,ny;

void init() {
  int i,j;
  nx = ny = 0;
  for (i = 0; i < MAXY; i++) {
    for (j = 0; j < MAXX; j++) {
      maze[i][j] = ' ';
      stat[i][j] = -1;
    }
  }
}

void readMaze() {
  char c;
  int posx = 1;
  int posy = 1;
  while ((c = (char)getchar()) != EOF) {
    if (c == '\n') {
      if (posx) {
	nx = posx;
	posy++;
      }
      posx = 1;
    } else {
      maze[posy][posx++] = c;
      if (c == 'S') {
	stat[posy][posx-1] = 0;
      }
    }
  }
  ny = posy;
}

void printMaze() {
  int i,j;
  printf("The maze is %i by %i.\n",nx-1,ny-1);
  for (i = 1; i < ny; i++) {
    for (j = 1; j < nx; j++) {
      printf("%c",maze[i][j]);
    }
    printf("\n");
  }
}

int solveMaze() {
  int i,j,k;
  int keepGoing = 1;
  int lookAt = 0;
  int ni,nj;
  while (keepGoing) {
    for (i = 1; i < ny; i++) {
      for (j = 1; j < nx; j++) {
	if (stat[i][j] == lookAt) {
	  for (k = 0; k < 4; ) {
	    ni = i + srch[k];
	    nj = j + srch[((k++)+1)%4];
	    if (maze[ni][nj] == 'E')
	      return lookAt+1;
	    if (maze[ni][nj] != 'W' && stat[ni][nj] == -1)
	      stat[ni][nj] = lookAt+1;
	  }
	}
      }
    }
    lookAt++;
  }
  return -1;
}

int main(int argc, char* argv[]) {
  int l;
  init();
  readMaze();
  l = solveMaze();

  printf("There are %i steps to the exit.\n",l);

  return 0;
}
