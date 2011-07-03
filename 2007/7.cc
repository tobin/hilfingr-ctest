#include <iostream>

/* This program outputs a description of a state machine for
   multiplying binary numbers by a fixed integer, k.  The
   state machine accepts its input and provides its output
   in binary digits, least-significant-bit first. 

   The state machine was derived from this bit of psuedocode:

   int A = 0;              // accumulator
   while (c = getbit()) {
     if (c & 1) 
       A += N;
     output (A & 1);
     A = A >> 1;
   }

   Tobin Fricke
   Berkeley Programming Contest 2007, Problem 7.
*/

using namespace std;

int main(int argc, char **argv) {
  int k;
  while ((cin >> k) && (k >= 0)) {
    cout << "To multiply by " << k << ":" << endl;
    for (int A=0; (A<k)||(A==0); A++) 
      cout << A << "\t" <<                                  // Current state
	(A & 1) << "\t" << (A >> 1) << "\t" <<              // Output and next-state if we get a zero
	((A + k) & 1) << "\t" << ((A + k) >> 1) << endl;    // Output and next-state if we get a one
    cout << endl;
  }
  return 0;
}
