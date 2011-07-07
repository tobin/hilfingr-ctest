#include "contest.h"

struct le { 
 char * word;
 struct le * next; } * lex , *nl;

int match(char * abbr, char * word) {
// printf("matching %s | %s\n", abbr, word);
 if (*abbr == 0) return 1;
 if (*word == 0) return 0;
 return *abbr == *word && match(abbr+1, word+1) || match(abbr,word+1);
}

char * minw;
int min;
char w[1000];

int main() {

  while (scanf("%s", w) == 1) {
	if (strcmp(w,"/") == 0) break;
	nl = malloc(sizeof(struct le));
	nl -> next = lex;
	nl->word = strdup(w);
	lex = nl;
  }
  scanf("%*[\n]");

  while (1) {
	*w = 0;
	if (scanf("%[^a-zA-Z0-9]", w) < 0) exit(0);
	printf("%s", w);
	if (scanf("%[a-zA-Z0-9]", w) != 1) exit(0);
	if (*w == 0) exit(0);

	nl = lex;
	min = 1000;
	minw = 0;
	while (nl) { 
	  if (match(w, nl->word))  {
	   //printf("Match!\n");
		  if (strlen(nl->word) == min) { minw = 0; }
		  if (strlen(nl->word) < min) { 
		   min = strlen(nl->word);
		   minw = nl->word;
		   }
		}
	  nl = nl->next;
	}
	printf("%s", minw ? minw : w);
  }
}

