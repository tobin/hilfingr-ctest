#include <stdio.h>
#include <stdlib.h>

int abs(int i) { 
  return (i > 0 ? i : -i); 
}

struct restraint {
  int val;
  int *vars;
};

int check(int N, int k, int bindings[], struct restraint problem[]) {
  for (int i=0; i<N; i++) {
    int v = 0;
    for (int j=0; problem[i].vars[j] != 0; j++) {
      int var = abs(problem[i].vars[j]);
      if (var > k) 
	goto outer;
      int not = problem[i].vars[j] < 0;
      v = v ^ (not ? !bindings[var] : bindings[var]);
    }
    if (v != problem[i].val) return 0;
    outer:
    ;
  }
  return 1;
}

/* k is the higest variable that's already been bound. */

int solve(int N, int k, int bindings[], struct restraint problem[]) {
  int v;

  if (!check(N, k, bindings, problem))
    return 0;

  if (N==k)
    return 1;
  
  for (v = 0; v <= 1; v++ ) {
    bindings[k+1] = v;
    if (solve(N, k+1, bindings, problem))
      return 1;
  }

  return 0;
}

int main(int argc, char **argv) {
  int N;
  while (scanf("%d", &N)==1 && N>0) {
    int n;
    struct restraint problem[N];
    for (int i=0; i<N; i++) {
      scanf("%d %d", &n, &(problem[i].val));
      problem[i].vars = (int *)calloc(n+1, sizeof(int));
      for (int j=0; j<n; j++) 
	scanf("%d", &(problem[i].vars[j]));
    }
    int bindings[N+1];
    
    static int circuit = 1;
    printf("Circuit %d: ", circuit++);
    
    if (solve(N, 0, bindings, problem)) {
      for (int i=1; i<=N; i++)
	printf("%d ", bindings[i]);
      printf("\n\n");
    } else {
      printf("No solution found.\n\n"); 
    }

  }
  return 0;
}
