#include <iostream>
#include <string>

using namespace std;

char s_char(char c) {
  switch (toupper(c)) {
  case 'B':
  case 'P':
  case 'F':
  case 'V':
    return '1';
  case 'C':
  case 'S':
  case 'K':
  case 'G':
  case 'J':
  case 'Q':
  case 'X':
  case 'Z':
    return '2';
  case 'D':
  case 'T':
    return '3';
  case 'L':
    return '4';
  case 'M':
  case 'N':
    return '5';
  case 'R':
    return '6';
  default:
    return 'X';
  }
}

string soundex(string s) {
  string output = "";
  int broken = 0;
  output += s_char(s[0]);
  for (int i = 1; i<s.length(); i++) {  
    // skip characters we shouldn't encode
    if (s_char(s[i]) == 'X') {
      broken = 1;
      continue;
    }
    if (s_char(s[i]) == output[output.length()-1])
      if (!broken) 
	continue;
    if (output.length()==4)
      break;
    // add the next character
    output += s_char(s[i]);    
    broken = 0;
  }
    
  while (output.length() < 4) 
    output += '0';
  output[0] = toupper(s[0]);
  return output;
}

int main(int argc, char **argv[]) {
  string s;
  while (cin >> s) {
    cout << s << " => " << soundex(s) << endl;
  }
  return 0;
}
