#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <utility>
#include <iterator>

using namespace std;

set<string> find_palindromes(string s) {
  set<string> results, veto;
  /* Search for palindromes centered at each string position, c */
  for (unsigned int c=1; c<s.length(); c++) {
    /* When k=0, we search for palindromes like ABCBA.
       When k=1, we search for palindromes like ABBA */
    for (int k=0; k<2; k++) {
      vector<string> int_results;
      /* Search outward from the center, verifying that the Palindrome 
         property is maintained. */
      int maxlen = min(c+1, s.length() - c + k);
      for (int len=1; len < maxlen && (s.at(c-len)==s.at(c+len-k)); len++)  {
        /* Every intermediate result is a Palindrome */
	int_results.push_back(s.substr(c-len, 2*len+1-k));
      }
      if (int_results.size()>0) {
        /* Keep only the last (longest) palindrome found on this sweep. */
	results.insert(int_results.back());
        /* Add all of the centered sub-palindromes to the veto list. */
	int_results.pop_back();
	veto.insert(int_results.begin(),int_results.end());
      }
    }
  }
  /* Remove the items in the veto list from the results. */
  for (set<string>::iterator i=veto.begin(); i != veto.end(); i++)
    results.erase(*i);
  return results;
}

/* Extract the alpha characters from a string, and put them in upper case. 
   i.e. "Madam, I'm Adam." --> "MADAMIMADAM"                               */
string string_clean(string str) {
  string buffer = "";
  for (unsigned int i=0; i<str.length(); i++) 
    if (isalpha(str[i]))
      buffer += toupper(str[i]);
  return buffer;
}

/* The main program is a REPL loop for Palindrome-finding. */
int main(int argc, char **argv) {
  string input;
  while (getline(cin,input)) {
    input = string_clean(input);
    set<string> pals = find_palindromes(input);
    copy(pals.begin(), pals.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
  }
  return 0;
}

