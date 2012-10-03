#include <stdio.h>
#include <assert.h>

int *counts = 0;

int visit(int n, int b) {
  int sum = 0;
  if (n<0) return 0;
  if (n==0) { // base case
    int ii=0;
    while (counts[ii] >= 0) {
      sum += counts[ii];
      ii++;
    }
    return sum;
  }  
  for (int ii=0; ii<b; ii++) 
    sum += visit(n-b, b-1);
  return sum;
}

// n = number of digits
// b = base
int count_lucky_tickets(int n, int b) {
  assert((2 <= b) && (b <= 10));
  assert(n % 2 == 0);

  counts = (int *)calloc(n, sizeof(int));
  counts[n] = -1;

  int result = visit(n, b);
  free(counts);

  // "The answers will always be less than 2^(63)"
  return result;
}

int main(int argc, char **argv) {
  int digits, base;
  while (2 == scanf("%d %d", &digits, &base)) {
    int result = count_lucky_tickets(digits, base);
    printf("There are %d %d-digit base %d lucky numbers.\n",
	   result, digits, base);
  }
  return 0;
}
