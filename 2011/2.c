#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>

/* Count lucky bus tickets of a given length and base.

   A lucky bus ticket has the sum of the first half of its digits
   equal to the sum of the second half of its digits.

   Tobin Fricke
   2013-04-26
 */

uint64_t **table = 0;   // for memoization

/* Count n-digit numbers in base b with sum s */
uint64_t L(int n, int s, int b) {
  if ((s < 0) || (s > n*(b-1))) 
    return 0;

  if (n == 1) 
    return (s >= 0) && (s < b);

  if (!table[n][s]) {
    uint64_t result = 0;
    for (int d=0; d<b; d++) 
      result += L(n-1, s-d, b);
    table[n][s] = result;
  }

  return table[n][s];
}

int main(int argc, char **argv) {
  int N;  // number of digits in the whole serial number
  int B;  // base 

  while (2==scanf("%d %d", &N, &B)) {
    assert((N>0) && (N%2 == 0));  // n is a positive even number
    assert((B>=2) && (B<=10));    // base is between 2 and 10 (inclusive)

    // Allocate the dynamic programming table
    table = (uint64_t **)calloc(N+1, sizeof(uint64_t *));
    for (int n=0; n<=N; n++) {
      table[n] = (uint64_t *)calloc(n*(B-1)+1, sizeof(uint64_t));
    }

    // Solve the problem
    uint64_t count = 0;
    for (int s=0; s<(N*(B-1)); s++) {
      uint64_t with_this_sum = L(N/2, s, B);
      count += with_this_sum * with_this_sum;
    }

    // Be a good citizen and free the memory
    for (int n=0; n<(N+1); n++) 
      free(table[n]);
    free(table);

    printf("There are %lu %d-digit base %d lucky numbers.\n", count, N, B);
  }
  return 0;
}
