#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Tobin Fricke
   tobin at xcf.berkeley.edu
   2003-03-07

   algorithm: fixed point iteration
*/

double max(double x, double y) {
  return (x>y ? x : y);
}

int main(void) {
  int m,n; 
  while (2 == scanf("%d %d",&m,&n)) {
    double ponds[2][m+2][n+2];
    memset(ponds,0,2*(m+2)*(n+2)*sizeof(double));

    for (int j=0; j<2; j++)
      for (int i=0; i<m; i++) scanf("%lf",&(ponds[0][i+1][j ? 0 : n+1]));
    for (int j=0; j<2; j++)
      for (int i=0; i<n; i++) scanf("%lf",&(ponds[0][j ? 0 : m + 1][i+1]));
    
    for (double maxdiff = 0; maxdiff < 0.05;) {
      maxdiff = 0;
      memcpy(ponds[1],ponds[0],(m+2)*(n+2)*sizeof(double));  // ponds[1] = ponds[0]
      for (int i=1; i<m+1; i++)
	for (int j=1; j<m+1; j++) {
	  for (int k=-1; k<=1; k++)
	    for (int l=-1; l<=1; l++) 
	      if ((k==0 || l==0) && (k || l)) 
		ponds[0][i][j] += 0.25 * (ponds[1][i+k][j+l] - ponds[1][i][j]);
	  maxdiff = max(maxdiff, abs(ponds[0][i][j] - ponds[1][i][j]));
	}
    }
    
    for (int j=0; j<n+2; j++) 
      for (int i=0; i<m+2; i++) 
	if ((i==0 || i==m+1) + (j==0 || j==n+1) < 2) 
	  printf("%d ",(int)(ponds[0][i][j]));
    printf("\n");
  }
  return 0;
}










