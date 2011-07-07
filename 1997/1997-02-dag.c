#include "contest.h"

int num[10001], denom[10001];
int a,b,nn,dd;

void hit(int * ar, int n) {
 int p = 1;
 while (n > 1) { p++;
  while (n % p == 0) ar[p]++, n /= p;
 }
}

int main() {

 while (scanf("%d/%d", &a,&b) == 2) { hit(num,a); hit(denom,b); }

 nn = dd = 1;
 for (a = 2; a < 10001; a++)  {
  if(num[a] != 0 && denom[a] != 0)
   if (num[a] >= denom[a])
	 num[a] -= denom[a], denom[a] = 0;
	else
	 denom[a] -= num[a], num[a] = 0;
	  
  while (num[a]-- != 0) nn *= a;
  while (denom[a]-- != 0) dd *= a;
 }

 printf(dd == 1 ? "%d\n" : "%d/%d\n", nn,dd);
 exit(0);
}
