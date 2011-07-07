#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int bindings[26];
bool digit_used[10];
char variables[11];
int n_variables;
unsigned int places;
char a[128],b[128],c[128];

bool fail(void) {
  assert(false);
  return false;
}

bool leading_digit(char var) {
  return (a[strlen(a)-1] == var) || (b[strlen(b)-1] == var) || (c[strlen(c)-1] == var);
}

bool bound(char c) {
  assert((c >= 'a' && c <= 'z') || c==0);
  if (c==0) return true;
  return bindings[c-'a']>=0;
}

int binding(char c) {
  if (c == 0) return 0;
  assert(c >= 'a' && c <= 'z');
  assert(bound(c));
  return bindings[c-'a'];
}

bool bind(char c, int value) {
  assert(c >= 'a' && c <= 'z');
  assert(value >= 0 && value <= 9);
  if (bound(c)) {
    assert(false);
    return(false);
  }
  if (digit_used[value])
    return false;
  if (value==0 && leading_digit(c))
    return false;
  digit_used[value] = true;
  bindings[c-'a'] = value;
  return true;
}


bool unbind(char c) {
  assert(c >= 'a' && c <= 'z');
  assert(bound(c));
  if (!bound(c)) {
    assert(false);
    return(false);
  }
  digit_used[binding(c)] = false;
  bindings[c-'a'] = -1;
  return true;
}

bool still_possible(void) {
  int carry[129];
  
  bzero(carry,sizeof(int)*(places+1));

  for (unsigned int place = 0; place < places; place++) {
    int sum;

    if ((!bound(a[place])) || (!bound(b[place])))
      return true;

    sum = binding(a[place]) + binding(b[place]) + carry[place];
    carry[place+1] = sum / 10;
    
    if (bound(c[place])) {
      if (binding(c[place]) != sum % 10)
	return false;
    } else {
      if (! bind(c[place], sum % 10))
	return false;
    }
  }
  return (carry[places]==0);
}

/* reverse a string in place */

void reverse(char *string) {
  int end;
  end = strlen(string)-1;
  for (int i=0; i<((end+1)/2); i++) {
    char temp;
    temp = string[i];
    string[i] = string[end-i];
    string[end-i] = temp;
  }
}

/* add a variable to the list of variables.  return true iff successful */

bool add_variable(char var) {
  assert(n_variables < 10);
  assert('a' <= var && var <= 'z');
  if ((n_variables >= 10) || (var < 'a' || 'z' < var))
    return false;
  if (0 == strchr(variables,var)) 
    variables[n_variables++] = var;
  return true;
}

/* search for a possible binding for the nth variable assuming all previous
   variables are already bound. */

bool search(int var) {
  if (var == n_variables) 
    return still_possible();
  
  if (bound(variables[var]))
    return search(var+1);
  
  for (int value=0; value<10; value++) {
  
    if (! bind(variables[var],value))
      continue;
    
    if (still_possible()) {
      if (search(var+1))
	return true;
    }

    for (int i=var; i<n_variables; i++) 
      if (bound(variables[i]))
	unbind(variables[i]);
    still_possible();
  }
  return false;
}

int max2(int a, int b) { return (a > b ? a : b); }
int max3(int a, int b, int c) {
  return max2(max2(a,b),c);
}

void substitute(char *string) {
  unsigned int len = strlen(string);
  for (unsigned int i=0; i<len; i++) {
    if (string[i] >= 'a' && string[i] <= 'z')
      string[i] = binding(string[i])+'0';
  }
}

void leftpad(char *str, unsigned int len) {
  reverse(str);
  while (strlen(str)<len) strcat(str," ");
  reverse(str);
}

void output_puzzle(bool exists) {
  
  char *oa, *ob, *oc, *sa, *sb, *sc;
  
  leftpad(oa=strdup(a),places);
  leftpad(ob=strdup(b),places);
  leftpad(oc=strdup(c),places);
  
  if (exists) {
    substitute(sa = strdup(oa));
    substitute(sb = strdup(ob));
    substitute(sc = strdup(oc));
  }
  
  printf("  %s",oa);
  if (exists) printf("     %s",sa);
  printf("\n+ %s",ob);
  if (exists) printf("   + %s",sb);
  printf("\n");
  for (unsigned int i=0; i<2+places; i++) printf("-");
  if (exists) {
    printf("   ");
    for (unsigned int i=0; i<2+places; i++) printf("-");
  }
  printf("\n  %s",oc);
  if (exists)
    printf("     %s\n",sc);
  else
    printf("     No solution\n");
  free(oa);
  free(ob);
  free(oc);
  if (exists) {
    free(sa);
    free(sb);
    free(sc);
  }
  
  printf("\n");
}

int main(int argc, char **argv) {
  bzero(a,sizeof(char)*128);
  bzero(b,sizeof(char)*128);
  bzero(c,sizeof(char)*128);
  
  while (3 == scanf("%s %s %s",a,b,c)) {

    for (int i=0; i<26; i++) bindings[i] = -1;
    for (int i=0; i<10; i++) digit_used[i] = false;
    bzero(variables,sizeof(char)*11);
    n_variables = 0;

    reverse(a);
    reverse(b);
    reverse(c);

    places = max3(strlen(a),strlen(b),strlen(c));
    
    bool result = true;

    for (unsigned int place=0; place<places; place++) {
      if (place < strlen(a)) result |= add_variable(a[place]);
      if (place < strlen(b)) result |= add_variable(b[place]);
      if (place < strlen(c)) result |= add_variable(c[place]);
      if (!result) break;
    }

    if (result)
      result = search(0);

    reverse(a);
    reverse(b);
    reverse(c);

    output_puzzle(result);

    bzero(a,sizeof(char)*128);
    bzero(b,sizeof(char)*128);
    bzero(c,sizeof(char)*128);

  }
  return 0;
}







