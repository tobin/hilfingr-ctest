// Return all matching substrings to given set of strings
// only deal with alphabetic characters ('a' - 'z' and 'A' - 'Z')
// case insensative
// By: Chris Spitzer

#include <stdio.h>
#include <string.h>

#define MAX_WORD_SIZE 64

char* *words[26];
int wordsN[26];
char *dictionaryName = "/usr/share/dict/words";

int getKey(char a) {
  if (a >= 'a' && a <= 'z')
    return a - 'a';
  if (a >= 'A' && a <= 'Z')
    return a - 'A';
  return -1;
}

int testValidity(char *w) {
  do {
    if (getKey(*w) < 0)
      return 0;
  } while (*(++w) != 0);
  return 1;
}

int buildDictionary() {
  FILE *dict;
  char *buf = 0;
  int ind;
  int indCt[26];
  char c;
  if ((dict = fopen(dictionaryName,"r")) == NULL) {
    printf("Unable to open dictionary file.\n");
    return 0;
  }
  buf = (char*)malloc(MAX_WORD_SIZE);
  for (ind = 0; ind < 26; ind++) {
    wordsN[ind] = 0;
    indCt[ind] = 0;
  }
  while (fscanf(dict,"%s",buf) == 1) {
    if ((ind = getKey(buf[0])) >= 0 && testValidity(buf))
      wordsN[ind] += 1;
  }
  for (c = 'a'; c <= 'z'; c++) {
    words[getKey(c)] = (char**)calloc(wordsN[getKey(c)],sizeof(char*));
    for (ind = 0; ind < wordsN[getKey(c)]; ind++)
      words[getKey(c)][ind] = 0;
  }
  rewind(dict);
  while (fscanf(dict,"%s",buf) == 1) {
    if ((ind = getKey(buf[0])) >= 0 && testValidity(buf)) {
      words[ind][indCt[ind]] = (char*)calloc(strlen(buf)+1,sizeof(char));
      strcpy(words[ind][indCt[ind]],buf);
      indCt[ind] += 1;
    }
  }
  free(buf);
  return 1;
}

void destroyDictionary() {
  char c;
  int ind;
  int i;
  for (c = 'a'; c <= 'z'; c++) {
    ind = getKey(c);
    for (i = 0; i < wordsN[ind]; i++) {
      free(words[ind][i]);
      words[ind][i] = 0;
    }
    free(words[ind]);
    words[ind] = 0;
  }
}

void countLetters(char *s, int *cnt) {
  int wordLength;
  int i;
  wordLength = strlen(s);
  for (i = 0; i < 26; i++)
    cnt[i] = 0;
  for (i = 0; i < wordLength; i++)
    cnt[getKey(s[i])] += 1;
}

void doWord(char *s) {
  int sourceCnt[26];
  int dictCnt[26];
  int i,j,k;
  int isMatch;
  int wantComma;
  countLetters(s,sourceCnt);
  printf("Word: %s\nForms: ",s);
  wantComma = 0;
  for (i = 0; i < 26; i++) {
    if (sourceCnt[i] == 0)
      continue;
    for (j = 0; j < wordsN[i]; j++) {
      countLetters(words[i][j],dictCnt);
      isMatch = 1;
      for (k = 0; k < 26; k++) {
	if (dictCnt[k] > sourceCnt[k]) {
	  isMatch = 0;
	  break;
	}
      }
      if (isMatch) {
	if (wantComma)
	  printf(", ");
	printf("%s",words[i][j]);
	wantComma = 1;
      }
    }
  }
  if (!wantComma)
    printf("*none*");
  printf("\n");
}

int main(int argc, char *argv[]) {
  char *buf;
  if (!buildDictionary()) {
    printf("Error building dictionary.\n");
    return 0;
  }
  buf = (char*)malloc(MAX_WORD_SIZE);

  while (scanf("%s",buf) == 1) {
    doWord(buf);
  }

  destroyDictionary();
  return 0;
}
