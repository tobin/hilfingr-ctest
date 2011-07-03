#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int i, int j) {
 return (i>j?i:j);
}

int lcs(char *a, char *b, int i, int j) {
  int retval;
  static int **table;
  if (i==0 && j==0) {
    table = (int **)calloc(sizeof(int *), strlen(a));
    for (int k=0; k<strlen(b); k++) 
      table[k] = (int *)calloc(sizeof(int), strlen(b));
  }
  if (table[i][j]>0)
    retval = table[i][j]-1;
  else if (a[i]==0 || b[j]==0)
    retval = 0;
  else if (a[i]==b[j])
    retval = 1+lcs(a,b,i+1,j+1);
  else
    retval = max(lcs(a,b,i+1,j+1),max(lcs(a,b,i+1,j), lcs(a,b,i,j+1)));
  table[i][j] = retval+1;
  if (i==0 && j==0) {
    free(table);
    table = 0;
  }
  return retval;
}

int main(int argc, char **argv) {
  char *a, *b;
  while (2==scanf("%as %as",&a,&b)) {
    printf("%d\n", lcs(0,0));
  }  
  return 0;
}
