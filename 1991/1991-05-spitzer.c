// Solves Bounded Post's Correspondence Problem for two sets of
// strings
// By: Chris Spitzer

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXM 20
#define MAXS 12
#define BUFSIZE 32

typedef struct {
  char* x[MAXM];
  char* w[MAXM];
  int k;
  int setsize;
  void *nextProb;
} PROB;

PROB *probs;

void init() {
  probs = 0;
}

int isWhitespace(char c) {
  return (c == ' ' || c == '\t');
}

void readInput() {
  PROB *curProb;
  PROB *nextProb;
  char *buf;
  char c;
  int len;
  int pos = 0;
  int bufpos = 0;
  int setpos = 0;
  int whichSet = 0;
  buf = (char*)malloc(BUFSIZE);
  curProb = probs;
  // state machine
  while ((c = (char)getchar()) != EOF) {
    switch (pos) {
    case 0: // no number yet
      if (c >= '0' && c <='9') {
	buf[bufpos++] = c;
	pos = 1;
	nextProb = (PROB*)malloc(sizeof(PROB));
	(*nextProb).nextProb = 0;
	setpos = 0;
	if (curProb) {
	  (*curProb).nextProb = nextProb;
	} else {
	  probs = nextProb;
	}
	curProb = nextProb;
      }
      break;
    case 1: // inside number
      if (c >= '0' && c <= '9') {
	buf[bufpos++] = c;
      } else {
	buf[bufpos] = '\0';
	(*curProb).k = atoi(buf);
	bufpos = 0;
	pos = 2;
      }
      break;
    case 2: // no string yet
      if (c == '\n') {
	goto hack_newline;   // The horror
      } else if (!isWhitespace(c)) {
	buf[bufpos++] = c;
	pos = 3;
      }
      break;
    case 3: // inside string
      if (c == '\n') {
	buf[bufpos] = '\0';
	len = strlen(buf);
	if (whichSet == 0) {
	  (*curProb).x[setpos] = (char*)malloc(len+1);
	  strcpy((*curProb).x[setpos],buf);
	} else {
	  (*curProb).w[setpos] = (char*)malloc(len+1);
	  strcpy((*curProb).w[setpos],buf);
	}
      hack_newline:
	if (whichSet == 0) {
	  (*curProb).setsize = setpos+1;
	  setpos = 0;
	  whichSet = 1;
	  bufpos = 0;
	  pos = 2;
	} else if (whichSet == 1) {
	  setpos = 0;
	  whichSet = 0;
	  bufpos = 0;
	  pos = 0;
	}
      } else if (isWhitespace(c)) {
	buf[bufpos] = '\0';
	len = strlen(buf);
	if (whichSet == 0) {
	  (*curProb).x[setpos] = (char*)malloc(len+1);
	  strcpy((*curProb).x[setpos],buf);
	} else {
	  (*curProb).w[setpos] = (char*)malloc(len+1);
	  strcpy((*curProb).w[setpos],buf);
	}
	bufpos = 0;
	setpos += 1;
      } else {
	buf[bufpos++] = c;
      }
      break;
    }
  }
  free(buf);
}

void printProb(PROB *p, int n) {
  int i;
  if (!p) {
    printf("Null Problem\n");
    return;
  }
  printf("Problem %i:\n",n);
  printf("K=%i\n",(*p).k);
  for (i = 0; i < (*p).setsize; i++)
    printf("%s ",(*p).x[i]);
  printf("\n");
  for (i = 0; i < (*p).setsize; i++)
    printf("%s ",(*p).w[i]);
  printf("\n");
}


void printProbs() {
  PROB *p = probs;
  int i = 1;
  while (p) {
    printProb(p,i++);
    p = (*p).nextProb;
  }
}

void solveProb(PROB *p) {
  int n,j,k,a;
  int *i;
  int foundSol = 0;
  char *bufx;
  char *bufw;
  int posx;
  int posw;
  if (!p)
    return;
  n = (*p).setsize;
  k = (*p).k;
  if (n <= 0 || k <= 0)
    return;
  i = (int*)calloc(k,sizeof(int));
  bufx = (char*)malloc(k*BUFSIZE);
  bufw = (char*)malloc(k*BUFSIZE);
  for (j = 0; j < k; j++)
    i[j] = 0;
  while (!foundSol) {
    posx = 0;
    posw = 0;
    for (j = 0; j < k; j++) {
      strcpy(&bufx[posx],(*p).x[i[j]]);
      posx += strlen((*p).x[i[j]]);
      strcpy(&bufw[posw],(*p).w[i[j]]);
      posw += strlen((*p).w[i[j]]);
    }
    if (strcmp(bufx,bufw) == 0) {
      foundSol = 1;
    } else {
      a = 1;
      for (j = 0; j < k; j++) {
	i[j] += a;
	if (i[j] > (n-1)) {
	  i[j] = 0;
	} else {
	  a = 0;
	}
      }
      if (a)
	foundSol = 2;
    }
  }
  if (foundSol == 1) {
    printf("Solution: ");
    for (j = 0; j < k; j++)
      printf("%i ",i[j]+1);
    printf("\n");
  } else {
    printf("No solution.\n");
  }
  free (i);
  free(bufx);
  free(bufw);
}

void solveProbs() {
  PROB *p = probs;
  int i = 1;
  while (p) {
    printProb(p,i++);
    solveProb(p);
    p = (*p).nextProb;
  }
}

void cleanup() {
  PROB *p = probs;
  PROB *lastp;
  int i;
  while (p) {
    for (i = 0; i < (*p).setsize; i++) {
      free((*p).x[i]);
      free((*p).w[i]);
    }
    lastp = p;
    p = (*p).nextProb;
    free(lastp);
  }
}

int main(int argc, char* argv[]) {
  init();
  readInput();
  solveProbs();
  cleanup();

  return 0;
}
