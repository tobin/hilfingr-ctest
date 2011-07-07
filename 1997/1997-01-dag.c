#include "contest.h"

struct li { struct li * next;
  int x1, x2, y1, y2; } * lines, *newline , *scan;
struct pp { int x, y; } * player;

int lineside(long long ax, long long ay, long long bx, long long by, long long cx, long long cy) {
 long long p = ax*by - ay*bx + ay*cx - ax*cy - by*cx + bx*cy;
 if (p > 0) return 1;
 if (p < 0) return -1;
 return 0;
}

int n,i,p,x,y,prevx,prevy,a,b,c,d,playing;


int main () {
// printf("%d\n", sizeof(long long));
  scanf("%d %d", &n, &p);
  player = malloc(p * sizeof(struct pp));

  for (i = 0; i < p; i++)  {
	scanf("%d %d", &player[i].x, &player[i].y);

	newline = malloc(sizeof(struct li));
	newline->x1 = newline->x2 = player[i].x;
	newline->y1 = newline->y2 = player[i].y;
	newline-> next = lines; lines = newline;
  }

  playing = 0;
  while (scanf("%d %d", &x, &y) == 2 && x != -1 && y != -1) {
	prevx = player[playing].x;
	prevy = player[playing].y;

	newline = malloc(sizeof(struct li));
	newline->x1 = prevx, newline->x2 = x;
	newline->y1 = prevy, newline->y2 = y;
	scan = lines;
	while (scan) {
	  // if lines intersect, where newline is assumed to lack first point.

	  a = lineside(scan->x1, scan->y1, scan->x2, scan->y2, x, y);
	  b = lineside(scan->x1, scan->y1, scan->x2, scan->y2, prevx, prevy);
	  c = lineside(prevx, prevy, x, y,scan->x1, scan->y1);
	  d = lineside(prevx, prevy, x, y,scan->x2, scan->y2);

	  if (a * b <= 0 && b != 0 && c * d <= 0)
	  {
	  printf("Player %d loses on moving to peg (%d, %d)\n", playing, x,y);
	  exit(0);
	  }
	  scan = scan->next;
	}
	newline-> next = lines; lines = newline;

	player[playing].x = x;
	player[playing].y = y;
	playing = (playing + 1) % p;
  }

  printf("All players are still in the game\n");
	
  exit(0);
}



