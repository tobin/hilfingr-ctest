#include <iostream>
#include <unordered_map>
#include <set>
#include <string>
#include <queue>
#include <utility>
#include <iterator>

using namespace std;
bool debug = false;
#define D if (debug)

/* We'll implement the friend-graph as a mapping from a friend's name to a set 
   of their friends (seems simple enough).
*/

int main(int argc, char **argv) {
  int N;
  string C;
  int n = 0;
  while(cin >> N >> C) {
    D cout << "Set #" << ++n << ":" << endl;

    unordered_map<string, set<string>> graph;

    string F1, F2;  // two friends' names
    while ((cin >> F1 >> F2) && (F1 != "*")) {
      graph[F1].insert(F2);        // F1 and F2 are friends
      graph[F2].insert(F1);
    }

    // Print out the graph, just to check
    D cout << " Client is " << C << ", who wants " << N << " new friends" << endl;
    D for (auto p : graph) {
      cout << " " << p.first << ": ";
      for (auto q : p.second) {
	cout << q << " ";
      }
      cout << endl;
    }

    /* Find the friends-of-friends-of-C, and keep track of how many
       friends they have in common with C. */

    unordered_map<string, int> friends_in_common;

    for (auto f1 : graph[C])   // f1 is a friend-of-C
      for (auto f2 : graph[f1]) // f2 is a friend-of-a-friend
	if (!graph[C].count(f2) && f2 != C) // make sure C isn't already friends with f2
	  friends_in_common[f2] ++;  

    /* We want strings that are "lesser" to come FIRST.  Unfortunately
       that means we need to redefine the comparison method on pairs.
       Alternatively, maybe we could just use std::less. */

    struct mycompare {
      bool operator() (const pair<int,string>& lhs, const pair<int,string>& rhs) {
	if (lhs.first < rhs.first)
	  return true;
	if (lhs.second > rhs.second)
	  return true;
	return false;
      }
    };

    /* Load the potential friends into the priority queue so that they
       will be ranked first by the number of friends in common with C,
       and secondly by their names in alphabetical order. */

    priority_queue<pair<int, string>, vector< pair<int,string> >, mycompare> mypq; 
    for (auto kv : friends_in_common) {
      mypq.push(make_pair(kv.second, kv.first));
      D cout << kv.first << " has " << kv.second << " friends in common with " << C << endl;
    }

    /* One final complication... the specification asks for the new
       friends to be ranked togetehr in alphabetical order (not first
       by number of common friends).  We'll load them into a sorted
       container to have it do this for us. */

    set<string> new_friends;
    for (int i=0; i<N; i++) {
      new_friends.insert(mypq.top().second);
      mypq.pop();
    }

    /* Finally we can produce the output. */

    copy(new_friends.begin(), new_friends.end(), ostream_iterator<string>(cout, " "));
    cout << endl;

  }
  return 0;
}
