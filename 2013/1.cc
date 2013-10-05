#include <iostream>
#include <climits>
#include <iomanip>

using namespace std;

#define D if (0)

int main(int argc, char **argv) {

  int N;

  while (cin >> N) {

    int ix0 = INT_MIN;
    int ix1 = INT_MAX;
    
    int iy0 = INT_MIN;
    int iy1 = INT_MAX;
    
    int iz0 = INT_MIN;
    int iz1 = INT_MAX;

    int vol = 0;

    D cout << "============================================================" << endl;
    for (int n=0; n<N; n++) {
  
      // now read N cubes
      int x, y, z, s;
      cin >> x >> y >> z >> s;
      
      /* The newly read cube occupies the intervals [x, x+s], [y, y+s],
	 [z, z+s] along the three axes.  
	 
	 The existing cube occupies [ix0, ix1], [iy0, iy1], [iz0, iz1].
      */
      
      D cout 	     << "Got cube with   "
	     << "x:[" << x << ", " << x+s << "], " 
	     << "y:[" << y << ", " << y+s << "], "
	     << "z:[" << z << ", " << z+s << "], with volume " << s*s*s << endl;

      ix0 = max(ix0, x);
      ix1 = min(ix1, x+s);
      if (ix0 > ix1) ix1 = ix0;

      iy0 = max(iy0, y);
      iy1 = min(iy1, y+s);
      if (iy0 > iy1) iy1 = iy0;

      iz0 = max(iz0, z);
      iz1 = min(iz1, z+s);
      if (iz0 > iz1) iz1 = iz0;

      int dx = ix1 - ix0;
      int dy = iy1 - iy0;
      int dz = iz1 - iz0;
      
      vol = dx*dy*dz;    
      
      D cout << "Intersection is "
	     << "x:[" << ix0 << ", " << ix1 << "], " 
	     << "y:[" << iy0 << ", " << iy1 << "], "
	     << "z:[" << iz0 << ", " << iz1 << "], with volume " << vol << endl;
    }


    cout << vol << endl;

  } 
  return 0; 
}
