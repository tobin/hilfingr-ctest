#include "contest.h"
#include <assert.h>

int N = 0;
int B = 0;
int M = 10000;
int ballots[10000][100];

#define D if (0)

// count how many ballots prefer a to b
int prefered_over(int a, int b) {
  int count = 0;
  for (int i=0; i<B; i++) {
    //    if (ballots[i][a] == 0 || ballots[i][b] == 0)
    //  continue; // not ranked
    //    if (ballots[i][b] == 0) {
    //  if (ballots[i][a]!=0)
    //count ++;
    //  } else
    if (ballots[i][a] <  ballots[i][b])
      count ++;
  }
  return count;

}

int main(int argc, char **argv) {

  // number of candidates
  scanf("%d", &N);
  D printf("Number of candidates: %d\n", N);
  assert(N<100);
  // read the ballots
  while (1) {
    for (int i=0; i<N; i++) {
      char str[255];
      int ranking;
      if (1!=scanf("%s", str))
	goto foo;
      if (strcmp(str, "-")==0)
	ranking = INT_MAX;
      else 
	ranking = atoi(str);
      ballots[B][i] = ranking;      
    }
    B++;
    assert(B<M);
  }
 foo:
  D printf("Read %d ballots\n", B);
  
  int winner_found = 0;
  // consider candidate 'a'
  for (int a=0; a<N; a++) {
    int has_been_defeated = 0;
    // consider opponents 'b'
    for (int b=0; b<N; b++) {
      if (a == b) 
	continue;
      D printf("Considering %d versus %d...\n", a, b);
      if (!(prefered_over(a,b) > prefered_over(b,a))) {
	has_been_defeated = 1;
	D printf("defeated\n");
	break;
      }
    }
    if (!has_been_defeated) {
      winner_found = 1;
      printf("Candidate #%d wins.\n", a+1);
      break;
    }
  }
  if (!winner_found) 
    printf("Election goes to the House.\n");

  return 0;
}
