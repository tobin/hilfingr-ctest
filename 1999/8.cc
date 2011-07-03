/* Fall 1999 Berkeley Programming Contest
   Solution to problem #8

   Tobin Fricke <tobin@csua.berkeley.edu>

   discussion: http://nibot-lab.livejournal.com/56189.html
 */

#include <algorithm>
#include <string>
#include <iostream>

int main(int argc, char **argv) {
  using namespace std; 
   string x;
   while (cin >> x) {
    cout << x << " -> ";
    next_permutation(x.begin(),x.end());
    cout << x << "\n";
  }
  return 0;
}
