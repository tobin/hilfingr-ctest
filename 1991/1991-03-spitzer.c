// Takes input of form:
//   S11&S12&S13&...&S1m
//   S21&S22&S23&...&S2m
//     ...
//   Sn1&Sn2&Sn3&...&Snm
// and prints out the Syx strings centered in columns delimited by |'s
// By: Chris Spitzer

#include <stdio.h>
#include <string.h>

#define MAXM 28
#define MAXN 60
#define BUFSIZE 256

char* words[MAXN][MAXM];
int numN,numM;

void readInput() {
  char *buf;
  int pos,m,n;
  int i;
  char c;
  pos = m = n = 0;
  buf = (char*)malloc(BUFSIZE);
  while ((c = (char)getchar()) != EOF) {
    if (c == ' ' && pos == 0) {
      continue;
    }
    if (c == '&' || c == '\n') {
      while ((pos-1)>0 && buf[pos-1]==' ')
	pos--;
      words[n][m] = (char*)malloc(pos+1);
      strncpy(words[n][m],buf,pos);
      words[n][m][pos] = '\0';
      if (c == '&') {
	m++;
      } else {
	numM = m+1;
	m = 0; n++;
      }
      pos = 0;
      continue;
    } 
    buf[pos++] = c;
  }
  numN = n;
  free(buf);
}

void printOutput() {
  int i,j,k,l,n;
  int *colWidths;
  colWidths = (int*)calloc(numM,sizeof(int));
  for (i = 0; i < numN; i++) {
    for (j = 0; j < numM; j++) {
      if ((l=strlen(words[i][j])) > colWidths[j])
	  colWidths[j] = l;
    }
  }
  for (i = 0; i < numN; i++) {
    for (j = 0; j < numM; j++) {
      printf(" ");
      l = strlen(words[i][j]);
      n = ((colWidths[j]-l)/2) + ((colWidths[j]-l)%2);
      for (k = 0; k < n; k++)
	printf(" ");
      printf("%s",words[i][j]);
      n = ((colWidths[j]-l)/2);
      for (k = 0; k < n; k++)
	printf(" ");
      if (j != (numM-1))
	printf(" |");
    }
    printf("\n");
  }
  free(colWidths);
}

void init() {
  int i,j;
  for (i = 0; i < MAXN; i++) {
    for (j = 0; j < MAXM; j++) {
      words[i][j] = 0;
    }
  }
}

void cleanup() {
  int i,j;
  for (i = 0; i < MAXN; i++) {
    for (j = 0; j < MAXM; j++) {
      if (words[i][j]) {
	free(words[i][j]);
	words[i][j] = 0;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  init();
  readInput();
  printOutput();
  cleanup();
  
  return 0;
}
