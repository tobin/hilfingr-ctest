#include "contest.h"

int visit[1000], typ[1000];
int a[1000],b[1000];
int n;
int out;
int start, target, p,q, i,m,c,j;


int main() {
 scanf("%d %d", &start, &target);
 while (scanf("%d %d", &p, &q) == 2) {
 if (p < 0 || q < 0) break;
 typ[p] = q;
 }
 while (scanf("%d %d", &p, &q) == 2) {
 if (p < 0 || q < 0) break;
 a[n] = p, b[n] = q;
 n++;
 a[n] = q, b[n] = p;
 n++;
 }

 visit[start] = 1;
 c = 1;

 do {
   m =0;
   for (i = 0; i < 1000; i++) 
	if (visit[i] == c)  {
	 // printf("%d Visiting %d, type %d\n", c, i, typ[i]);
	  m++;
	  if (typ[i] == target) visit[i] = -1;
	  else 
	   for (j = 0; j < n; j++) {
		if (a[j] == i && visit[b[j]] == 0) visit[b[j]] = c+1;
		}
	}
   c++;
 } while (m > 0);

 printf("Starting at %d, you might first encounter type %d shop #",
   start,target);
 for (i = 0; i < 1000; i++)
  if (visit[i] == -1) printf(out ? ", %d" : "%d" ,i), out = 1;
 printf("\n");
 return 0;
}



  


