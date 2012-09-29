// Tobin Fricke 2012-09-29

#include <contest.h>

int main(int argc, char **argv) {
  uint64_t x;
  while (cin >> x) {
    
    int c = 0; 
    int digits[64];
    for (int i=0; i < 64; i++) {
      int bit = !!(x & ((uint64_t)1 << i));
      digits[63-i] = bit;
      c += bit;
    }

    int P = 0;
    while (prev_permutation(digits, digits+64))  // sorry
      P++;

    cout << x << " is number " << P+1 << 
      " in the sequence of numbers with " << c << " 1-bits." << endl;
    }

  return 0;
}
