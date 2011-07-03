#include <stdio.h>
#include <string.h>

// Binomial coefficient
int choose(int n, int k) {
  if (k==0) return 1;
  if (n==0) return 0;
  return choose(n-1, k-1) + choose(n-1, k);
}

// how many characters come before this one?
int value(char *s) {
  int val = 0;
  int len = strlen(s);
  int a   = 'a';

  while (s[0]) {
    if (s[0] < a || s[0] > 'z') 
      return 0;  // Not a valid sequence

    val += (choose('z' - a + 1, len) - choose('z' - s[0] + 1, len))
      + choose('z' - 'a' + 1, len - 1);
    
    // This is essentially a recursive call to value() :
    a = s[0] + 1;
    s ++;
    len --;    
  }
  return val ;
}

int main(int argc, char **argv) {
  char s[28];
  while (EOF != scanf("%s",s)) {
    printf("%d\n", value(s));
  }
  return 0;
}
