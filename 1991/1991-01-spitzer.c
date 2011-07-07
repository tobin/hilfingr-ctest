// Find the position of number with n bits in list of all numbers with n bits
// By: Chris Spitzer

#include <stdio.h>

#define MAX_BITS 16
#define MAX_NUM (1 << MAX_BITS)

int pasc[MAX_BITS][MAX_BITS];

void init() {
  int i,j;
  for (i = 0; i < MAX_BITS; i++) {
    pasc[i][i] = 1;
    pasc[i][0] = i+1;
  }
  for (i = 1; i < MAX_BITS; i++) {
    for (j = 1; j < i; j++) {
      pasc[i][j] = pasc[i-1][j] + pasc[i-1][j-1];
    }
  }
}

void getBitInfo(int n, int *numBits, int *length) {
  int pos = 1;
  int c;
  (*length) = 0;
  (*numBits) = 0;
  for (c = 1; c <= MAX_NUM; c = c << 1, pos++) {
    if (c & n) {
      (*length) = pos;
      (*numBits) += 1;
    }
  }
}

int findPos(int n) {
  int i;
  int b,l,c;
  getBitInfo(n,&b,&l);
  if (b < 2)
    return l-1;
  c = 0;
  for (i = 0; i < l - b; i++) {
    c += pasc[b-2+i][b-2];
  }
  return c + findPos(n - (1 << (l-1)));
}

int main(int argc, char* argv[]) {
  int ns,ne,p,b,l;

  init();
  if (argc > 1) {
    ns = 1; ne = 50;
  } else {
    scanf("%i",&ns);
    ne = ns;
  }
  for ( ; ns <= ne; ns++) {
    getBitInfo(ns,&b,&l);
    p = findPos(ns);
    printf("%i is number %i in the sequence of numbers with %i 1-bits.\n",ns,p,b);
  }
  
  return 0;
}
