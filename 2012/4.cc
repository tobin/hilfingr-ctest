// Tobin Fricke - 2012-09-29

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

struct PairHasher {
  size_t operator()(const pair<string, string>& p) const {
    hash<string> hash_fn;
    return hash_fn(p.first) + hash_fn(p.second);
  }
};

typedef unordered_map<pair<string,string>, int, PairHasher> Map;

int edit_distance(string s, string t) {
  static Map memo;
  auto i = memo.find(make_pair(s,t));
  if (i != memo.end())
    return i->second;

  int result;

  if (s.length() == 0)
    result = t.length();
  else if (t.length()==0)
    result = s.length();
  else {
    int cost = 0;
    if (s[0] != t[0])
      cost = 2;
    int a = edit_distance(s.substr(1,s.length()-1), t) + 1;
    int b = edit_distance(s, t.substr(1,t.length()-1)) + 1;
    int c = edit_distance(s.substr(1,s.length()-1), t.substr(1,t.length()-1)) + cost;
    result = (a < b ? a : b);
    result = (c < result ? c : result);
  }

  memo[make_pair(s,t)] = result;
  return result;

}

int main(int argc, char **argv) {
  string s, t;
  while (getline(cin, s) && getline(cin, t))
    cout << edit_distance(s,t) << endl;
			  
  return 0;
}
