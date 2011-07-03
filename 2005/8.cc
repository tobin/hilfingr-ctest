#include "contest.h"

int pos(int x, int y) {
/*
  if (x==0 && y==0)
    return 0;
  if (y == 0)
    return 1 + pos(0, x-1);
  else
    return 1 + pos(x + 1, y - 1);
*/
  int N = x + y;
  return N*(N+1)/2 + y;
}

int main(void) {
  int N;
  while (1 == scanf("%d",&N) && N>0) {
    for (int i=0; i<N; i++) {
      int x1, y1, x2, y2, pos1, pos2, steps;
      scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
      pos1 = pos(x1,y1);
      pos2 = pos(x2,y2);
 //     printf("pos1 = %d, pos2 = %d\n", pos1, pos2);
      steps = (pos1 > pos2) ? (pos1 - pos2) : (pos2 - pos1) ;
      printf("Case %i: (%d, %d) to (%d, %d) takes %d %s\n",
	i+1, x1, y1, x2, y2, steps, steps==1 ? "step" : "steps");
    }
  }
  return 0;
}
