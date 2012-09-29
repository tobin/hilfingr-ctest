#include <contest.h>


typedef pair<int,int> thing;

pair<string,string> parse(string s) {
  string result;
  string token;
  pair<string,string> foo;
  while (s.length() > 0) {
    char c = s[0];
    s = &s[1];
    switch (c) {
      
    case '+': 
    case '-': 
    case '.':
      token = c;
      result += token;
      break;
      
    case '(':      
      foo = parse(&s[0]);
      token = foo.first;
      s = foo.second;
      result += token;
      break;
      
    case ')':
      return pair<string,string>(result,s);
      
    case '9': result += token;
    case '8': result += token;
    case '7': result += token;
    case '6': result += token;
    case '5': result += token;
    case '4': result += token;
    case '3': result += token;
    case '2': result += token;
    case '1': 
      break;
      
    default:
      cout << "syntax error";
      exit(1);
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
    //    cout << s << " --> " << foo.first << endl;
    double result = run(foo.first);
    cout << setiosflags(ios::fixed) << setprecision(2);
    cout << "Average value of " << s << " is " << result << endl;
  }
  return 0;
}
