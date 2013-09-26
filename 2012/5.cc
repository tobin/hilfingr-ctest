/* Berkeley Programming Contest
   Fall 2012
   Problem #5
   Tobin Fricke <tobin@pas.rochester.edu>

   The drawing of "surveyor's lines" is a graph, where each line
   segment is a graph edge and each vertex is identified by its
   coordinate pair.  I store this graph using an adjacency list
   representation.  This is implemented as a map from <x,y> pairs to
   lists of reachable verticies (also represented as <x,y> pairs).

   We travel clockwise around the outer perimeter of the graph.
   Whenever we find an edge going into the interior, we take it, alays
   taking the "most clockwise" edge until we get back to where we
   started.

*/

#include <iostream>
#include <unordered_map>
#include <map>
#include <list>
#include <algorithm>

using namespace std;
bool debug = false;

typedef pair<int,int> point;   // Used to represent a point (x,y)

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

/* In order to find which edge is "most clockwise" or "most
   counter-clockwise" with respect to a given incoming ray, it's
   useful to sort rays by the angle they form with the incoming
   ray. This function computes the angle between the ray pivot-->src
   and pivot-->dst, from 0 to 360 degrees.
*/

double angle_from(point src, point pivot, point dst) {
  src = src - pivot;
  dst = dst - pivot;
  double x = dst.first * src.first  + dst.second * src.second;  // dot product   = |a| |b| cos theta
  double y = dst.first * src.second - dst.second * src.first;   // cross product = |a| |b| sin theta
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

// This is our actual adjacency-list storage of the graph
typedef unordered_map<point, list<point>, PointHasher > Map;

// Read in the problem statement from standard input
Map read_segments(int n_segments, point &start) {

  int start_x = 99999; // infinity
  int start_y;
  Map graph;

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
  start = make_pair(start_x, start_y);
  return graph;
}

// Solve the problem
map<int, int> explore_graph(Map graph, point start) {
  map<int, int> histogram;
  point current = start;   
  point prev = make_pair(current.first, current.second - 1);  // approach first node from below

  do {
    if (debug) cout << "current = " << current << endl;

    // Sort the list of reachable nodes by their angle from the
    // starting vertex
    auto reachable = graph[current];
    reachable.sort(SortByAngle(prev, current));
      
    // remove back-link
    reachable.pop_front();
      
    // get the next forward link
    point next = reachable.front(); 
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

  return histogram;
}

int main(int argc, char **argv) {

  int n_segments;
  int cases = 0;
  while ((cin >> n_segments) && (n_segments > 0)) {
    cout << "Case " << ++cases << ":" << endl;
    map<int, int> histogram;
    Map graph;
    point start;

    graph = read_segments(n_segments, start);

    if (debug) 
      cout << "Read " << n_segments << " segments" << endl;

    histogram = explore_graph(graph, start);

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
