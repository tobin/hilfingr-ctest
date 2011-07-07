#include <stdio.h>

/* Tobin Fricke
   September 24, 2001
   Berkeley Programming Contest, problem 1998-01
*/

void go(int a, int b) {

  if (a==0) return;

  if (b<0) {
    a = -a; 
    b = -b;
  }

  if (a > 0) {
   
    int n = a/b + (b*(a/b)==a ? 0 : 1); 
    go(a - b*n,b);

    printf("+%d",n);

  } else {
    
    go(-b,a);
    printf("/");
  }
}


int main(int argc, char **argv) {
  int a,b;

  while (2 == scanf("%d %d",&a,&b)) {

    printf("%d/%d: ",a,b);
    go(a,b);
    printf("\n");
  }

  return 0;
}
