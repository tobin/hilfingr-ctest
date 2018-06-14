#include <iostream>
#include <assert.h>
#include <map>
#include <tuple>

using namespace std;

// Return true iff the string of length m starting at i comes before
// the string starting at j.
bool circular_strcmp(string s, int m, int i, int j,
                           map<tuple<int,int,int>, bool> &memo) {
  int N =s.length();

  if (memo.count(tuple<int, int, int>(m, i, j)))
    return (memo.find(tuple<int, int, int>(m, i, j))->second);

  bool result;

  if (m == 0)
    result = false;
  else if (s.at(i) < s.at(j))
    result = true;
  else if (s.at(i) > s.at(j))
    result = false;
  else
    result = circular_strcmp(s, m-1, (i+1) % N, (j+1) % N, memo);

  memo[tuple<int, int, int>(m, i, j)] = result;
  return result;
}

int main(int argc, char **argv) {
  int N;
  string s;

  while (cin >> N >> s) {
    assert(N == s.length());
    int best_so_far = 0;
    for (int i=0; i<N; i++) {
      map<tuple<int,int,int>, bool> memo;
      if (circular_strcmp(s, N, i, best_so_far, memo)) {
        best_so_far = i;
      }
    }
    cout << best_so_far + 1 << endl;
  }
  return 0;
}
