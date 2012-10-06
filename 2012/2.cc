/* Fractions

   This program accepts a sequence of fractions on standard input, and
   outputs the product of these fractions.  The key feature is that the
   calculation should succeed even if some intermediate product of the
   numerators or denominators would overflow.   The approach taken is 
   to factor everything into prime factors.
   
   Tobin Fricke - 2012-10-05
 */

#include <set>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

typedef multiset<unsigned int> factorlist;

// operator- = set difference
factorlist& operator-=(factorlist &a, factorlist const &b) {
  factorlist tmp;
  set_difference(a.begin(), a.end(),  
		 b.begin(), b.end(), inserter(tmp, tmp.begin()));
  swap(tmp, a);
  return a;
}

// operator+ = insert
factorlist& operator+=(factorlist &lhs, const factorlist& rhs) {
  lhs.insert(rhs.begin(), rhs.end());
  return lhs;
}

// operator& = intersection
factorlist operator&(factorlist const &a, factorlist const &b) {
  factorlist tmp;
  set_intersection(a.begin(), a.end(),  
		   b.begin(), b.end(), inserter(tmp, tmp.begin()));
  return tmp;
}

// product of elements
int prod(factorlist x) {
  return accumulate(x.begin(), x.end(), 1, multiplies<int>());
}

factorlist factorize(unsigned int N) {
  factorlist result;

  for (unsigned int p=2; (N != 1) && (p*p <= N); p += (p==2 ? 1 : 2)) 
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
    num += factorize(n);
    den += factorize(d);
  }

  factorlist com = num & den;     // Find the common factors

  num -= com;                // Remove the common factors 
  den -= com;
  
  cout << prod(num) << "/" << prod(den) << endl;

  return 0;		   
}
