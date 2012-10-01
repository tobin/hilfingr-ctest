#include <stdio.h>
#include <inttypes.h>

// Binomial coefficient
uint64_t choose(int n, int k) {
  static uint64_t memo[65][65];
  if (memo[n][k] !=0) return memo[n][k];
  if (k==0) return 1;
  if (n==0) return 0;
  if (k<0 || k>n) return 0;
  if (k > n - k) k = n - k;
  uint64_t result = choose(n-1, k-1) + choose(n-1, k);
  memo[n][k]=result;
  return result;
}

int main(int argc, char **argv) {
  uint64_t x;
  while (scanf("%ld", &x)) {
    
    // count nonzero bits
    int c = 0;  
    for (int i=0; i < 64; i++) 
      c += !!(x & ((uint64_t)1 << i));

    // compute lexicographic index
    uint64_t P = 0;
    int remaining_ones = c;
    for (int i=0; i < 64; i++) 
      if (x & ((uint64_t)1 << (63 - i))) 
	P += choose(63 - i, remaining_ones--);

    printf("%ld is number %ld in the sequence of numbers with %d 1-bits.", x, P, c);
  }
  
  return 0;
}
