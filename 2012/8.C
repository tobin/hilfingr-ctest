#include <contest.h>
#include <assert.h>
/*


In[2]:= Binomial[64,10]
Out[2]= 151473214816
binom =   1149359456

 09 99 99 00   00 00 00 00

 */

// Tobin Fricke 2012-09-29

static uint64_t memo[65][65];

// Binomial coefficient
uint64_t choose(int n, int k) {

  if (memo[n][k] !=0) return memo[n][k];

  if (k==0) return 1;
  if (n==0) return 0;
  if (k<0 || k>n) return 0;
  if (k > n - k)
    k = n - k;
  uint64_t result = choose(n-1, k-1) + choose(n-1, k);
  memo[n][k]=result;
  return result;
}

/*

worst case:
In[3]:= Binomial[64,10]
Out[3]= 151 473 214 816
         71 775 589 931
 
*/

int main(int argc, char **argv) {
  for (int i=0; i<65; i++)
    for (int j=0; j<65; j++)
      memo[i][j]=0;

  //    cout << "binomial(64,10) = " << choose(64,10) << endl;
  //  cout << "binomial(10,5) = " << choose(10,5) << endl;
  uint64_t x;
  while (cin >> x) {
    
    int c = 0; 
    int digits[64];
    for (int i=0; i < 64; i++) {
      int bit = !!(x & ((uint64_t)1 << i));
      digits[63-i] = bit;
      c += bit;
    }

    // digits[0] is the most significant bit

    // compute lexicographic index
    uint64_t P = 0;
    int remaining_ones = c;
    for (int i=0; i < 64; i++) {
      if (digits[i]) {
	P += choose(63 - i, remaining_ones);
	remaining_ones --;
      }
	
    }


    cout << x << " is number " << P << 
      " in the sequence of numbers with " << c << " 1-bits." << endl;
    }

  return 0;
}
