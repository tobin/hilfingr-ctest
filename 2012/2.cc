/* Fractions

   This program accepts a sequence of fractions on standard input, and
   outputs the product of these fractions.  
   
   Tobin Fricke - 2012-10-05
 */

#include <set>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

typedef multiset<unsigned int> factorlist;

factorlist factorize(unsigned int N) {
  factorlist result;
  
  for (unsigned int p=2; (N != 1) && (p*p <= N); p++) 
    while (N%p == 0) {
      N /= p;
      result.insert(p);
    }
  
  if (N != 1)
    result.insert(N);
  
  return result;
}

int main(void) {
  
  unsigned int n, d;
  factorlist num, den;
  while (2==scanf("%d/%d",&n,&d)) {
    factorlist f = factorize(n);
    num.insert(f.begin(), f.end());
    f = factorize(d);
    den.insert(f.begin(), f.end());
  }

  // Find the common factors

  factorlist com; 
  set_intersection(num.begin(), num.end(), 
		   den.begin(), den.end(),
		   inserter(com, com.begin()));

  // Remove the common factors from the numerator and denominator
  factorlist tmp;  // why can't we do it in-place?
  set_difference(num.begin(), num.end(), 
		 com.begin(), com.end(), 
		 inserter(tmp, tmp.begin()));
  num = tmp;

  tmp.clear();
  set_difference(den.begin(), den.end(), 
		 com.begin(), com.end(), 
		 inserter(tmp, tmp.begin()));
  den = tmp;
  
  // Multiply the remaining factors together
  n = accumulate(num.begin(), num.end(), 1, multiplies<int>());
  d = accumulate(den.begin(), den.end(), 1, multiplies<int>());
  
  cout << n << "/" << d << endl;
  return 0;
		   
}
