#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  int N, D; // numerator, divisor
  while (cin >> N >> D) {
    cout << "As polynomials, " << N << " mod " << D << " = ";

    // do long division
    int Q = 0;
    int R = 0;
    for (int i=31; i>=0; i--) {
      R = R << 1;
      R = R | !!(N & (1 << i));
      if ((R ^ D) < R) {
	R = R ^ D;  // subtraction is xor
	Q = Q | (1 << i);
      }
    }
    
    cout << R << endl;

  }
  return 0;
  
}
