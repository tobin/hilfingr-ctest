
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int M, N;
char grid[80][81];

int find_paths(char *str, int r, int c) {
  int paths = 0;
  if (r<0 || r>=M || c<0 || c>=N) // check whether we're in bounds
    return 0;
  if (str[0] != grid[r][c]) // check whether the first character matches
    return 0;
  if (str[1]==0) // check whether this is the end of the string
    return 1;
  for (int ii=-1; ii<=1; ii++) // check all the compass directions
    for (int jj=-1; jj<=1; jj++) 
      if (ii || jj) 
	paths += find_paths(str+1, r+ii, c+jj);
  return paths;  
}

int main(int argc, char **argv) {
  int r, c;
  while (4 == scanf("%d %d %d %d", &M, &N, &r, &c)) {
    char str[80];
    scanf("%s", str);
    for (int ii=0; ii<M; ii++)
      scanf("%s", grid[ii]);
    int result = find_paths(str, r, c);
    printf("There are %d paths.\n", result);
  }
  return 0;
}
