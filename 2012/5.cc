#include <iostream>
#include <unordered_map>
#include <map>
#include <list>
#include <algorithm>

using namespace std;
bool debug = false;

/*
  The graph will be stored as a map from points (x,y) to a list of
  points that are reachable from there.
 */

typedef pair<int,int> point;

struct PointHasher {
  size_t operator()(const point& p) const {
    hash<int> hash_fn;
    return hash_fn(p.first) + hash_fn(p.second);
  }
};

point operator-(point &a, point &b) {
  return make_pair(a.first - b.first, a.second - b.second);
}


ostream& operator<<(ostream& ost, const point &p) {
  ost << "(" << p.first << "," << p.second << ")";
  return ost;
}

double angle_from(point dst, point pivot, point src) {
  src = src - pivot;
  dst = dst - pivot;
  double x = src.first * dst.first  + src.second * dst.second;  // dot product   = |a| |b| cos theta
  double y = src.first * dst.second - src.second * dst.first;   // cross product = |a| |b| sin theta
  double theta = atan2(y, x); 
  if (theta < 0)
    theta += 2 * M_PI;
  return theta * 180.0 / M_PI;
}


struct SortByAngle {
  point src, piv;
  SortByAngle(point src, point piv) : src(src), piv(piv) { }
  bool operator()(point first, point second){
    return angle_from(src, piv, first) < angle_from(src, piv, second);
  }
};

typedef unordered_map<point, list<point>, PointHasher > Map;


int main(int argc, char **argv) {

  int n_segments;
  int cases = 0;
  while ((cin >> n_segments) && (n_segments > 0)) {
    cout << "Case " << ++cases << ":" << endl;
    map<int, int> histogram;
    Map graph;
    int start_x = 99999;
    int start_y;
    for (int i=0; i<n_segments; i++) {
      int x[2], y[2];
      cin >> x[0] >> y[0] >> x[1] >> y[1];

      // Add this edge to the graph
      graph[make_pair(x[0],y[0])].push_back(make_pair(x[1],y[1]));
      graph[make_pair(x[1],y[1])].push_back(make_pair(x[0],y[0]));

      // Keep track of a starting point (upper left)
      for (int i=0; i<2; i++) {
	if ((x[i] < start_x) || ((x[i] == start_x) && (y[i] > start_y))) {
	  start_x = x[i];
	  start_y = y[i];
	}
      }


    }
    if (debug) 
      cout << "Read " << n_segments << " segments" << endl;

    point start = make_pair(start_x, start_y);
    point current = start;   
    point prev = make_pair(current.first, current.second - 1);  // approach first node from below

    do {
      if (debug)
	cout << "current = " << current << endl;
      // Sort the list of reachable nodes by their angle from the
      // starting vertex
      auto reachable = graph[current];
      reachable.sort(SortByAngle(prev, current));
      
      point next;
      
      // remove back-link
      reachable.pop_front();
      
      // get the next forward link
      next = reachable.front(); 
      reachable.pop_front();
      
      // If there are any more links, we have loops to go around      
      for (auto inner_start : reachable) {
	auto inner_current = inner_start;
	auto inner_prev = current;
	int hops = 0;

	if (debug) cout << current;
	do {
	  if (debug) cout << " --> " << inner_current;
	  hops ++;

	  auto reachable = graph[inner_current];
	  reachable.sort(SortByAngle(inner_prev, inner_current));

	  auto next = reachable.back();
	  inner_prev = inner_current;
	  inner_current = next;
	} while (inner_current != inner_start);

	if (debug) cout << endl;
	histogram[hops] ++;
      }
      
      // Go
      prev = current;
      current = next;
    } while (current != start);  

    // Output the histogram
    int total = 0;
    for (auto p : histogram) {
      cout << "  Lots with " << p.first << " surveyor's lines = " << p.second << endl;
      total += p.second;
    }
    cout << "Total number of lots = " << total << "\n" << endl;

  }

  return 0;
}
