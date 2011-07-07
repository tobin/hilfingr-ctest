#include <contest.h>

int matches(char *string, char *pattern) {
  char *found, *substr,*next;
  
  if (pattern[0] == 0) return 1;

  if (strstr(pattern,".*") == pattern) {
    while (strstr(pattern,".*") == pattern) pattern += 2;
    found = strstr(pattern,".*");
    if (found) {
      substr = strdup(pattern);
      substr[found - pattern] = 0;
    } else substr = pattern;
    // look for matches
    found = string;
    while (next = strstr(found, substr)) {
      if (matches(found+strlen(substr),pattern + strlen(substr)))
	return 1;
      found = next + 1;
    }
    return 0;
  } else if (found = strstr(pattern,".*")) {  // patern begins with plain text
    
    substr = strdup(pattern);
    substr[found - pattern] = 0;
    
    if (strstr(string,substr) != string)
      return 0;  // not a prefix
    else
      return matches(string+strlen(substr),pattern+strlen(substr));

  } else 
    // no more wildcards
    return(strstr(string,pattern)==string);
}


int readline(char *s) {
  char *buffer = calloc(1000,sizeof(char));
  char *foo = buffer;
  if (fgets(buffer,1000,stdin) == NULL) return 0;
  while (buffer[0] && isspace(buffer[0])) buffer ++;
  while (strlen(buffer)>0 && isspace(buffer[strlen(buffer)-1])) buffer[strlen(buffer)-1]=0;
  strcpy(s,buffer);
  free(foo);
  return 1;
}

struct _patterns {
  char *s;
  int r;
  int m;
} patterns[1000];

char *mailbox[1000];

int main(void) {
  int rule = -1;
  int p = 0;
  int done = 0;
  char s[10000];
  int i;

  while (readline(s) && (strcmp(s,"::"))) {

    if (strlen(s) == 0) continue;

    if (!strcmp(s,":0")) {  // new rule
      rule ++;
      continue;
    }
    
    if (s[0] == '*') {     // a pattern
      char *str;
      str = strdup(s+1);
      patterns[p].r = rule;       
      patterns[p].s = strdup(s+1);
      p++;
      continue;
    }
    mailbox[rule] = strdup(s);
  }

  while (readline(s)) 
    for (i=0; i<p; i++) 
      patterns[i].m = patterns[i].m || matches(s,patterns[i].s);
  
  for (i=0; i<=rule; i++) {
    int n, ok = 1;
    for (n = 0; n<p; n++) 
      if (patterns[n].r == i) 
	ok = ok && patterns[n].m;
    if (ok) {
      printf("%s\n",mailbox[i]);
      done = 1;
      break;
    }
  }

  if (!done) 
    printf("$DEFAULT\n");

  return 0;
}

