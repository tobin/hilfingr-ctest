#include "contest.h"

char pr[1600];
float score[1600];
int bpos[1600];
 // best score for a paragraph starting at char i...
float s,b,linescore;
int i,j,c,w,n;

int main() { 
  while (gets(pr)) {
	n = strlen(pr);
	for (i = 0; i < n; i++) score[i] = 9e30, bpos[i] = 0;
	score[n] = 0;
	score[n+1] = 0;

	for (i = n-1; i >= 0; i--) {
	  c = -1; w = pr[i] != ' ';
	  for (j = i; j <= n; j++, c++) 
		if ((j == n || pr[j] == ' ') && (j != n-1)) {
		 s = 30 - c;  if (j == n && s > 0) s = 0;
		 b = (s >= 0 ? 2*s: -5*s) / (w>1?w-1:1);
		 linescore = (0.1+b*b*b) * (0.1+b*b*b);
		 if (linescore + score[j+1] < score[i]) {
		   score[i] = linescore + score[j+1], bpos[i] = j; 
		   // printf("Score %f: %s\n", score[i], pr+i);
		   }
		 w++;
		}
	}

	i = 0;
	while (1) { i = bpos[i]; if (i < n) pr[i] = '\n'; else break; }
	puts(pr);
  }
  return 0;
}
