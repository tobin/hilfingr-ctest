#include <contest.h>

#define D if (0)

typedef pair<int,int> thing;

pair<string,string> parse(string s) {
  string result;
  string token;
  pair<string,string> foo;
  while (s.length() > 0) {
    char c = s[0];
    s = &s[1];

    if (c=='+' || c=='-' || c=='.') {
      token = c;
      result += token;
    } else if (c == '(') {
      foo = parse(&s[0]);
      token = foo.first;
      s = foo.second;
      result += token;
    } else if (c == ')') {
      
      return pair<string,string>(result,s);
    } else if (('0'<=c) && (c<='9')) {
      int number = 0;
      do {
	number *= 10;
	number += (c - '0');
	c = s[0];	
	s = &s[1];
      } while (('0'<=c) && (c<='9'));
      s = c + s; // unconsume
      //      cout << "parsed number " << number << endl;
      for (int i=0; i<number-1; i++) {
	result += token;
      }
    }
  }
      
  return pair<string,string>(result,s);
}

double run(string s) {
  double accum = 0;
  int steps = 1;
  int x = 0;
  for (unsigned int i=0; i<s.length(); i++) {
    switch (s[i]) {
    case '+': x++; break;
    case '-': x--; break;
    case '.': break;
    default: cout << "syntax error!" << endl;
    }
    accum += x;
    steps ++;
  }
  return accum / (double) steps;
}



int main(int argc, char **argv) {

  string s;
  while (cin >> s) {
    pair<string,string> foo = parse(s);
    D cout << s << " --> " << foo.first << endl;
    double result = run(foo.first);
    cout << setiosflags(ios::fixed) << setprecision(2);
    cout << "Average value of " << s << " is " << result << endl;
  }
  return 0;
}
