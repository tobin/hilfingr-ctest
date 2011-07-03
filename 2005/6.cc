#include "contest.h"

#define LITERAL  0
#define LAMBDA  1
#define PAIR  2

#define D if (0)

struct _term {
  int type;
  int lambda_depth;
  struct _term *parent;

  char *literal;

  struct _term *car, *cdr;

  struct _term *formal;
  struct _term *E;
};

int whitespace(char c) {
  return (c==' ' || c=='\n');
}

int is_lower_case_letter(char c) {
  return ('a' <= c && c <= 'z');
}

void die(char *msg) {
  printf("Error: %s", msg);
  exit(0);
}

void eat_whitespace() {
  char c;
  while (whitespace(c = getc(stdin)));
  ungetc(c, stdin);
}

char *read_identifier() {
  char *buffer = (char *)calloc(255, sizeof(char));
  char *str;
  int i = 0;
  char c;

  while (is_lower_case_letter(c = getc(stdin)))
    buffer[i++] = c;

  ungetc(c, stdin);
  str = strdup(buffer);
  free(buffer);
  return(str);
}

struct _term *read_term(struct _term *);

struct _term *read_literal(struct _term *parent) {
  D printf("reading a literal\n");
  struct _term *term = (struct _term *)calloc(1, sizeof(struct _term));
  term->type = LITERAL;
  term->literal = read_identifier();
  term->parent = parent;
  return term;
}

struct _term *read_pair(struct _term *parent) {
  D printf("reading a pair\n");
  struct _term *term = (struct _term *)calloc(1, sizeof(struct _term));
  term->type = PAIR;
  term->parent = parent;
  term->car = read_term(term);
  term->cdr = read_term(term);
  D printf("finished reading a pair\n");
  return term;
}

struct _term *read_lambda(struct _term *parent) {
  D printf("reading a lambda\n");
  struct _term *term = (struct _term *)calloc(1, sizeof(struct _term));
  term->type = LAMBDA;
  term->parent = parent;
  // the slash has already been eaten
  eat_whitespace();
  term->formal = read_literal(term);
  eat_whitespace();
  char c = getc(stdin);
  if (c != '.') die("expected . in lambda expression\n");
  term->E = read_term(term);
  return term;
}

struct _term *read_term(struct _term *parent) {
  eat_whitespace();
  if (feof(stdin))
    return 0;
  char c = getc(stdin);
  if (c == '(') {
    struct _term *term;
    eat_whitespace();
    c = getc(stdin);
    if (c=='\\') {
      // read lambda
      term = read_lambda(parent);
    } else {
      // read pair
      ungetc(c, stdin); // wasn't a lambda
      term = read_pair(parent);
    }
    eat_whitespace();
    c = getc(stdin);
    if (c != ')') die("expected closing parenthesis");    
    return term;
  } else {
    // read literal
    ungetc(c, stdin);
    return read_literal(parent);
  }  
}

void print_term(struct _term *term) {
  switch (term->type) {
  case LITERAL: 
    printf(" '%s' ", term->literal);
    break;
  case PAIR:
    printf("(");
    print_term(term->car);
    printf(" ");
    print_term(term->cdr);
    printf(")");
    break;
  case LAMBDA:
    printf("(\\");
    print_term(term->formal);
    printf(".");
    print_term(term->E);
    printf(")");
    break;
  default:
    printf("UNKNOWN");
    break;
  }
}

int find_identifier(struct _term *term, int depth, char *identifier) {
  //  printf("find_identifier...\n");
  if (term == 0) {
    //    printf("got to the root\n");
    return -1;
  }
  if (term->type == LAMBDA) {
    //  printf("found lambda that binds '%s'\n", identifier);
    if (strcmp(term->formal->literal, identifier)==0)
      return depth;
    else 
      return find_identifier(term->parent, depth+1, identifier);
  } else {
    //    printf("going up the food chain...\n");
    return find_identifier(term->parent, depth, identifier);
  }
}

void print_bruijn(struct _term *term) {
  int lambda_depth;
  switch (term->type) {
  case LITERAL: 
    lambda_depth = find_identifier(term, 0, term->literal);
    if (lambda_depth == -1)
      printf("%s", term->literal);
    else
      printf("%d", lambda_depth);
    break;
  case PAIR:
    printf("(");
    print_bruijn(term->car);
    printf(" ");
    print_bruijn(term->cdr);
    printf(")");
    break;
  case LAMBDA:
    printf("(\\.");
    //print_term(term->formal);
    //printf(".");
    print_bruijn(term->E);
    printf(")");
    break;
  default:
    printf("UNKNOWN");
    break;
  }
}

int main(void) {
  struct _term *term;

  while ((term = read_term(0))) {
    static int i=0;
    printf("Term %i: ",++i);
    print_bruijn(term);
    printf("\n");
  }

  return 0;
}

    
