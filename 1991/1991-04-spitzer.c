// Take a value K from standard input and returns the Kth prime
// number.  K < 250001, with 2 for K == 1
// By: Chris Spitzer

#include <stdlib.h>
#include <stdio.h>

#define MAXK 250000
#define MAXRECALL 350

unsigned int primes[MAXRECALL];
int numCalc;

void init() {
  primes[0] = 2;
  numCalc = 1;
}

unsigned int getPrime(int k) {
  int i,isPrime;
  int n = 1;
  unsigned int c = 1;
  if (k == 1)
    return 2;
  while (n < k) {
    c += 2;
    isPrime = 1;
    for (i = 1; i < numCalc; i++) {
      if (c%primes[i] == 0) {
	isPrime = 0;
	break;
      }
    }
    if (isPrime) {
      n += 1;
      if (n < MAXRECALL)
	primes[numCalc++] = c;
    }
  }
  return c;
}

int main(int argc, char *argv[]) {
  char buf[128];
  int k;
  unsigned int n;
  scanf("%s",buf);
  k = atoi(buf);
  if (k > MAXK) {
    printf("%i is too large\n",k);
    return 0;
  }
  init();
  n = getPrime(k);
  printf("Prime %i is %u\n",k,n);
  return 0;
}
