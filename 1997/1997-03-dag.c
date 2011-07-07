#include "contest.h"

#define MAX 100
char anames[MAX][65];
char bnames[MAX][65];
int n;
char name[65];
int taken[MAX], partner[MAX], 
 apref[MAX][MAX], bpref[MAX][MAX], awant[MAX][MAX], badmatch[MAX][MAX];

int findname(char ar[MAX][65], char * nm) {
  int i;
  for (i = 0; i < n; i++) if (strcmp(ar[i], nm) == 0) return i;
  fprintf(stderr,"Name not found!\n");
  return -1; // take that!
}

void probe(int todo) {
int i, p;
  if (todo == n) {
	for (i = 0; i < n; i++) 
	  printf("%s %s\n", anames[i], bnames[partner[i]]);
	exit(0);
  }
  else

  for (i = 0; i < n; i++)
	if (p = awant[todo][i], !badmatch[todo][p] && !taken[p]) {
	  taken[p] = 1; 
	  partner[todo] = p;
	  probe(todo+1);
	  taken[p] = 0;
	}
}

int main() {
int i,j,ii,k;
 scanf("%d", &n);

 for (i = 0; i < n; i++) {
  scanf("%s", anames[i]);
  if (i == 0)
   for (j = 0; j < n; j++) scanf("%s", bnames[j]),
   apref[i][j] = j, awant[i][j] = j;
  else
   for (j = 0; j < n; j++) scanf("%s", name),
   ii = findname(bnames,name), apref[i][ii] = j, awant[i][j] = ii;
 }
 for (i = 0; i < n; i++) {
   scanf("%s", name);
   ii = findname(bnames, name);
   for (j = 0; j < n; j++) scanf("%s", name),
   bpref[findname(anames, name)][ii] = j;
 }

 // now strike out
 for (i = 0; i < n; i++)
 for (j = 0; j < n; j++)
 for (k = 0; k < n; k++) 
 if (k != i && apref[k][j] <= apref[i][j] && bpref[k][j] <= bpref[i][j])
  badmatch[i][j] = k+1; 
	// some other lead has a higher preference, and the junior also has
	// a higher pref for that lead.

 /*
 for (i = 0; i < n; i++) { puts("");
 for (j = 0; j < n; j++) printf("%d ", apref[i][j]); }
 for (i = 0; i < n; i++) { puts("");
 for (j = 0; j < n; j++) printf("%d ", bpref[i][j]); }
 for (i = 0; i < n; i++) { puts("");
 for (j = 0; j < n; j++) printf("%d ", badmatch[i][j]); }
 /* */

 probe(0);

 return 0;
}


