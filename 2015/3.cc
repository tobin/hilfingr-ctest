#include <iostream>
#include <iomanip>
#include <string>
#include <map>

using namespace std;

double search(string from, string to, int T,
              map<string, map<string, double> > &graph) {

  if (T==0) return (from == to ? 1.0 : 0.0);

  // Try all the currencies we can get to from here.
  double best_so_far = 0.0;
  for (auto C: graph[from]) {
    double can_get = (1.0 / C.second) * search(C.first, to, T-1, graph);
    if (can_get > best_so_far)
      best_so_far = can_get;
  }
  return best_so_far;
}

int main(int, char **) {
  int N; // Number of edges in the graph.
  int T; // Maximum number of trades.

  while (cin >> N >> T) {
    map<string, map<string, double> > graph;

    for (int i=0; i<N; i++) {
      string C1, C2;
      double P;
      cin >> C1 >> C2 >> P;  // Can convert C2 to C1 at a rate of 1/P.
      graph[C2][C1] = P;
    }

    if (0)
      for (auto C2 : graph)
        for (auto C1: C2.second)
          cout << C2.first << " --> "  << C1.first << " for " 
               << C1.second << " " << C2.first << "/" << C1.first << endl;

    double best_so_far = 0.0;
    for (auto C2 : graph) {
      if (0) cout << "Trying trades starting with " << C2.first << endl;
      double can_get = search(C2.first, C2.first, T, graph);
      if (can_get > best_so_far)
        best_so_far = can_get;
    }
    cout << setprecision(3) << (best_so_far - 1.0) * 100.0  << "%" << endl;
  }
  return 0;
}
