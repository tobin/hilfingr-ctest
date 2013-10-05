#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <list>
#include <cmath>
using namespace std;

// Test whether the naive solution will pass the automated testing.
// Test whether C++11 is allowed.
//   * GCC Version is less than 4.7
//   * No range-based for-statements

int main(int argc, char **argv) {
  int N = 0;
  string s;
  while (getline(cin, s)) {
    stringstream str(s);
    double x, y;
    list< pair<double,double> > points;

    // Read the input
    while (str >> x >> y) 
      points.push_back(make_pair(x,y));

    // Calculate the diameter by brute force
    int max_dist = 0;
    for (auto p = points.begin(); p != points.end(); p++) 
      for (auto q = points.begin(); q != points.end(); q++) {
	double dx = q->first - p->first;
	double dy = q->second - p->second;
	double dist = dx*dx + dy*dy;
	if (dist > max_dist)
	  max_dist = dist;
      }    

    // Produce the output
    cout << "Set #" << ++N << ": Diameter is " <<
      fixed << setprecision(2) << sqrt(max_dist) << endl;
  }
  return 0;
}
