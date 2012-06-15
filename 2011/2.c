#include <stdio.h>
#include <assert.h>

int count_lucky_tickets(int digits, int base) {
  assert((2 <= base) && (base <= 10));
  assert(digits % 2 == 0);

  
  // "The answers will always be less than 2^(63)"

}

int main(int argc, char **argv) {
  while (2 == scanf("%d %d", &digits, &base)) {
    int result = count_lucky_tickets(digits, base);
    printf("There are %d %d-digit base %d lucky numbers.\n",
	   result, digits, base);
  }
  return 0;
}
