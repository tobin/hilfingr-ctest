#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char ***names;
int n;

int prefers(int l, int a1, int a2) {
  for (int a=0; a<n; a++) 
    if (0 == strcmp(names[l][1+a],names[a1][0])) 
      return 1;
    else
      if (0 == strcmp(names[l][1+a],names[a2][0]))
	return 0;
  assert(0);
}

int name_to_number(char *name) {
  for (int i=1; i<2*n; i++) 
    if (0 == strcmp(names[i][0],name))
      return i;
  assert(0);
}

int main(int argc, char **argv) {
  while (1 == scanf("%d",&n)) {
    int loc[n], cc[n], choice[n];     
    names = (char ***)calloc(sizeof(char**),2*n);
    for (int r=0; r<2*n; r++) {                                   // read input
      names[r] = (char **)calloc(sizeof(char *),n+1);
      for (int c=0; c<n+1; c++) { 
	names[r][c]=(char *)calloc(sizeof(char),65);
	scanf("%64s",names[r][c]);
      }
    }
    for (int i=0; i<n; i++) {                                 // initialization
      loc[i] = name_to_number(names[i][1]) - n; 
      cc[i] = -1;
      choice[i] = 0;
    }
    bool something_changed;
    do {
      something_changed = 0;
      for (int l=0; l<n; l++)                      // assistants choose leaders
	if ((cc[loc[l]] < 0) || prefers(loc[l]+n,l,cc[loc[l]])) 
	  cc[loc[l]] = l;
      for (int l=0; l<n; l++)                          // unchosen leaders move
	if (cc[loc[l]] != l) {
	  loc[l] = name_to_number(names[l][++choice[l] + 1]) - n;
          something_changed = 1;
        }
    } while (something_changed);
    for (int l=0; l<n; l++) 
      printf("%s %s\n",names[l][0],names[loc[l]+n][0]);       // produce output
  }
  return 0;
}
