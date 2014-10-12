#include <iostream>
#include <vector>
#include <math.h>
#include <limits>
#include <utility>
#include <algorithm>

#define D if (1)

using namespace std;

// 2D vector class
class vec {
public:
  double x, y;
  vec(double x0, double y0) : x(x0), y(y0) {}
  vec() : x(0), y(0) {}
};

double dot(const vec &a, const vec &b) { 
  return a.x*b.x + a.y*b.y; 
}

double norm(const vec &x) { 
  return sqrt(dot(x, x));  
}

vec operator*(double a, const vec &v) { 
  return vec(a*v.x, a*v.y); 
}

vec operator+(const vec &a, const vec &b) { 
  return vec(a.x + b.x, a.y + b.y);
}

vec operator-(const vec &a, const vec &b) { 
  return vec(a.x - b.x, a.y - b.y);
}

vec operator/(const vec &v, double a) {
  return (1/a) * v;
}

ostream& operator<<(ostream &out, vec &v) {
  out << "(" << v.x << ", " << v.y << ")";
  return out;
}

istream& operator>>(istream &in, vec &v) {
  in >> v.x >> v.y;
  return in;
}


/* Find the nearest point on a line segment A-->B, for a given point P */

vec nearest_seg_pt(vec A, vec B, vec P) {
  vec n = (B - A)/norm(B - A); // normed vector in direction of line
  vec x = dot((P-A),n) * n + A;  // closest point on line

  if ( dot(x-A, n) < 0 )
    return A; // closest point is the endpoint A
  else if (dot(x-A, n) > dot(B-A, n)) 
    return B; // closest point is the endpoint B
  else
    return x; // closest point is between A and B
}


pair<double,double> find_closest_segment(vec P, vector<vec> segs) {
  double best_dist = std::numeric_limits<double>::infinity();
  int best_seg = 0;
  double enroute = 0;

  for (auto ii=segs.begin(); ii+1 != segs.end(); ii++) {
    vec A = *ii;
    vec B = *(ii+1);
    vec x = nearest_seg_pt(A, B, P);
    double dist = norm(P - x);
    D cout << "Distance from segment " << ii - segs.begin() << ": " 
	   << dist << " meters " << endl;
    if (dist < best_dist) { 
      best_seg = (ii - segs.begin());
      best_dist = dist;
      enroute = norm(A - x);
    }
  }
  D cout << "Closest is segment #" << best_seg << ", "
	 << enroute << " meters along route. " << endl;
  return make_pair(best_seg, enroute);
}

double travel_time(int start_seg, double start_pos, int end_seg, double end_pos, 
		   vector<vec> segs, vector<double> segv) {
  if (start_seg > end_seg) 
    return -1;     // will never arrive

  double time = 0;
  while (start_seg < end_seg) {
    double seg_len = norm(segs[start_seg] - segs[start_seg+1]); // segment length
    double seg_vel = segv[start_seg];   // speed limit on segment
    time += (seg_len - start_pos) / seg_vel;
    start_seg ++;  // advance to start of next segment
    start_pos = 0;  
  }

  // Now we have start_seg == end_seg
  if (start_pos > end_pos)
    return -1;

  double seg_vel = segv[start_seg];   // speed limit on segment
  time += (end_pos - start_pos) / seg_vel;
  return time;
}


int main(int argc, char **argv) {
  int N; // number of segments in the route
  int C; // number of busses
  while (cin >> N >> C) {
    vector<vec> segs;
    vector<double> segv;

    D cout << "Segments: " << N << endl;
    D cout << "Busses:   " << C << endl << endl;

    vec P;   // Your reported position
    vec X;   // multi-purpose vector variable

    cin >> P >> X;
    segs.push_back(X);  // Start of route
        
    // Read segments
    for (int i=0; i<N; i++) {
      double segvel;
      cin >> segvel >> X;
      segs.push_back(X); // Next route endpoint
      segv.push_back(segvel);
    }
    
    D {
      for (auto ii=segs.begin(); ii+1 != segs.end(); ii++) 
	cout << "Segment " << ii - segs.begin() << ": " 
	     << *ii << "-->" << *(ii+1) 
	     << "\t with velocity " << segv.at(ii - segs.begin())
	     << endl;
      cout << endl;
    }

    D cout << "Passenger is reported to be at " << P << endl;
    pair<int,double> rsltP = find_closest_segment(P, segs);
    D cout << endl;

    // Read bus positions
    vector<double> arrivals;
    for (int ii=0; ii<C; ii++) {
      cin >> X; // Read bus position
      D cout << "Bus " << ii << " is reported to be at " << X << endl;
      pair<int,double> rsltB = find_closest_segment(X, segs);
      double T = travel_time(rsltB.first, rsltB.second, 
			     rsltP.first, rsltP.second,
			     segs, segv);
      if (T < 0) {
	D cout << "Has already passed the passenger." << endl;
      } else {
	D cout << "Will reach passenger in " << T << " seconds" << endl;
	arrivals.push_back(T);
      }      
      D cout << endl;
    }

    // Print out the arrival times (rounded to integer) in sorted order
    sort(arrivals.begin(), arrivals.end());
    for (auto ii=arrivals.begin(); ii != arrivals.end(); ii++)
      cout << int(*ii + 0.5) << endl;

  }
  return 0;
}
