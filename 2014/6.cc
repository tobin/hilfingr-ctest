#include <iostream>
#include <math.h>

using namespace std;

void findrat(double K, int &N, int &D) {

  /* 1 + 2 + 3 + ... + S = S (S + 1) / 2 
                         = (S^2 + S) / 2

     N^2 + N - 2*K = 0

     S = (-1 + sqrt(1 + 8*K)) / 2
  */

  // Figure out which diagonal we're on
  double diag = ceil((sqrt(1 + 8*K) - 1)/2.0);

  // Now find out where we are on the diagonal
  double diff = diag*(diag + 1)/2.0 - K;

  D = diag - diff;
  N = 1 + diff;

  return;
}

int main(int argc, char **argv) {
  double K;
  while (cin >> K) {
    int N, D;
    findrat(K, N, D);
    cout << (long long)K << " => " << N << "/" << D << endl;
  }
  return 0;
}
