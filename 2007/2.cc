#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

vector<string> dictionary;
vector<string> clean_dict;
map<string,int> memos;

string remove_junk(string s) {
  string r;
  for (unsigned int i=0; i<s.length(); i++) 
    if (isalpha(s[i]))
      r += toupper(s[i]);
  return r;
}

bool dict_contains(string r) {
  for (int i=0; i<clean_dict.size(); i++) 
    if (clean_dict[i] == r)
      return true;
  return false;
}

int remove(string s) {
  s = remove_junk(s);
  // memoization
  if (memos.find(s) != memos.end())
    return memos[s];
  int result = 0;  
  // try removing each of the letters in turn
  for (unsigned int pos = 0; pos < s.length(); pos ++) {
    string r = s;
    r.erase(pos, 1);
    if (dict_contains(r))
      result = max(result, 1 + remove(r));
  }
  // memoization
  memos[s] = result;
  return result;
}

void do_problem(int problem) {
  int best_result = -1;
  string best_word;
  for (int i=0; i<dictionary.size(); i++) {
    int this_result = remove(dictionary[i]);
    if (this_result > best_result) {
      best_result = this_result;
      best_word = dictionary[i];
    }
  }
  cout << "Problem " << problem << ": can remove " << 
    best_result << " letters from \"" << best_word << "\"" << endl;
  return;
}


int main(int argc, char **argv) {
  string s;
  int problem = 1;
  while (cin >> s) {
    if (s != ";") {      
      dictionary.push_back(s);
      clean_dict.push_back(remove_junk(s));
    } else {
      if (dictionary.size() == 0)
	break;
      do_problem(problem);
      problem ++;
      dictionary.clear();
      clean_dict.clear();
      memos.clear();
    }
  }
  return 0;
}
