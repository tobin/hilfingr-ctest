#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap_char(char *a, char *b) { char c; c = *a; *a = *b; *b = c; return; }
int  comp_char(char *a, char *b) { return ((*a) > (*b)); }

int main(int argc, char **argv) {
 char buffer[1024];
 int i, j, l;

 while (1 == scanf("%s",buffer)) {
  l = strlen(buffer);
  printf("%s -> ",buffer);

  /* find the "inflection point" */

  for (i=l-1; i>0; i--) 
   if (buffer[i]>buffer[i-1]) break;

  /* find the lowest sufficiently-high character of those available */

  for (j=l-1; j>0; j--)
   if (buffer[j]>buffer[i-1]) break;

  /* install the new character at the inflection point */

  swap_char(buffer+j,buffer+i-1);

  /* sort the chars to the right of the inflection point so as to minimize their value */

  qsort(buffer+i,l-i,1,comp_char);

  /* that's all! */

  printf("%s\n",buffer);
   
 }
 return 0;
}
