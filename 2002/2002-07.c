#include "contest.h"

#define min(x,y) (x<y ? x : y)
#define max(x,y) (x>y ? x : y)

int main(void) {
  int Px, Py,N,X[201],Y[201],i,inside = 0;

  scanf("%d %d %d",&Px,&Py,&N);
  for (i=0; i<N; i++) scanf("%d %d",X+i,Y+i);

  X[N] = X[0];
  Y[N] = Y[0];

  for (i=0; i<N; i++) 
    if ((Y[i+1] - Y[i]) &&   // not on the wall
	((Py > min(Y[i],Y[i+1])) && (Py < max(Y[i],Y[i+1])))) {

    double x, alpha;

    alpha = (Py - Y[i])/(Y[i+1] - Y[i]);
    x = alpha*X[i+1] + (1-alpha)*X[i];

    if (x < Px)
      inside ++;
  }

  printf("The prisoner is %s\n", (inside%2)?"confined":"free");

  return 0;
}




