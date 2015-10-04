#include <iostream>
#include <assert.h>
#include <cmath>
#include <algorithm>
#include <cstdio>

using namespace std;

bool intersects(double x1, double y1, double x2, double y2,
                double wx1, double wy1, double wx2, double wy2) {

  // Reduce the problem to a horizontal wall.
  if (wx1 == wx2) {
    swap(wx1, wy1);
    swap(wx2, wy2);
    swap(x1, y1);
    swap(x2, y2);
  }

  assert(wy1 == wy2);              // Wall is horizontal.
  if (wx1 > wx2) swap(wx1, wx2);   // Wall coords are left to right.
  assert(wx1 < wx2);
  // Calculate the x value where (x1,y1)-->(x2, y2) intersects the wall.

  if (y1 == y2) {
    // Wall is horizontal, and line connecting the people is horizontal too.
    // Unclear if we really need to handle this case.
    return false;
  }

  double t = (wy1 - y1) / (y2 - y1);
  double x = x1 + (x2 - x1) * t;

  if ((t<0.0) || (t>1.0))
    return false;
  else 
    return (x >= wx1) && (x <= wx2);
}

int main(int, char **) {
  double x1, y1, x2, y2, wx1, wy1, wx2, wy2;
  while (cin >> x1 >> y1 >> x2 >> y2 >> wx1 >> wy1 >> wx2 >> wy2) {

    // Figure out if the direct path intersects the wall

    double result;
    if (!intersects(x1, y1, x2, y2, wx1, wy1, wx2, wy2)) {
      // No intersection.
      result = hypot(x2 - x1, y2 - y1)/2.0;
    } else {
    // First go to one end of the wall.
      double a = hypot(x1 - wx1, y1 - wy1) + hypot(x2 - wx1, y2 - wy1);
      double b = hypot(x1 - wx2, y1 - wy2) + hypot(x2 - wx2, y2 - wy2);
      result = (a < b ? a : b)/2.0;
    }
    static int N = 0;
    printf("Case %d: %0.3f\n", ++N, result);
  }
  return 0;
}
