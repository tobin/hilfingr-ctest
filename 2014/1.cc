#include <iostream>
#include <assert.h>

using namespace std;

int val(char c) {
  assert(((c >= 'A') && (c <= 'Z')) || c == ' ');
  if ((c >= 'A') && (c <= 'Z'))
    return c - 'A';
  else return 'Z' - 'A' + 1;
}

char chr(int i) {
  char c = 'A' + i;
  if (c > 'Z') 
    c = ' ';
  return c;
}

string caesar(string s, int n) {
  for (int i=0; i<s.length()-1; i++) {
    s[i] = chr((val(s[i]) + n) % 27);
  }
  return s;
}

string decode(string c, string w) {
  string p; // plaintext
  for (int n=0; n<27; n++) {
    p = caesar(c, n);
    if ((p.find(" " + w + " ")!=string::npos) ||
	(p.find(w + " ")==0) ||
	(p.find(" " + w + ".")!=string::npos))
      break; // success!
    p = "FAILURE";
  }
  return p;
}

int main(int argc, char **argv) {
  assert(caesar("GALLIA EST OMNIS DIVISA IN PARTES TRES.", 5) == "LFQQNFEJXYETRSNXEIN NXFENSEUFWYJXEYWJX.");
  string line, word;
  while (getline(cin, line) && getline(cin, word)) {
    //    cout << "Line: \"" << line << "\"" << endl;
    //    cout << "Word: \"" << word << "\"" << endl;
    cout << decode(line, word) << endl;
  }
  return 0;
}
