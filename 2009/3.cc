#include "contest.h"
#include <assert.h>

#define D if (0)

int cache[256][256];

int correct_message(char *s, int first, int len) {

  assert(len > 0);
  int result = cache[first][len];

  D printf("correct_message('");
  D for (int i=0; i<len; i++) 
    printf("%c", s[first+i]);
  D printf("')");

  // memoization
  if (result > -1) { 
    D printf("memoized result: %d\n", result);
    return result;
  }
  
  D printf(".");
  // rule #1: p-z are the only correct one-character messages
  if (len == 1) 
    result = (s[first]>='p' && s[first] <='z');
  else {
    switch (s[first]) {
      // rule #2: N sigma is correct if sigma is correct
    case 'N':
      result = correct_message(s, first+1, len-1);
      break;
      // rule #3: {C,D,E,I} sigma tau
    case 'C':
    case 'D':
    case 'E':
    case 'I':
      for (int b=1; b<(len-1); b++) {
	// chars (1 ... b) are sigma, chars (b+1, ... len) are tau 
	if (correct_message(s, first + 1, b) && 
	    correct_message(s, first + 1 + b, len - 1 - b)) {
	  result = 1;
	  break;
	}
      }
      if (result == -1) 
	result = 0;
      break;
    default:
      // RULE #4: only messages fitting rules #1-#3 are correct
      result = 0;
    }
  }
  assert(result == 0 || result == 1);
  cache[first][len] = result;
  D printf("==%d\n", result);
  return result;
}

int main(int argc, char **argv) {
  char str[260];
  while (1 == scanf("%s", str)) {
    printf("%s ", str);
    // initialize the  memoization table
    for (int i=0; i<256; i++)
      for (int j=0; j<256; j++)
	cache[i][j] = -1;
    // do it
    int is_correct = correct_message(str, 0, strlen(str));
    printf("%s\n", is_correct ? "YES" : "NO");
  }
  return 0;
}
