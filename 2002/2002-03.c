#include <contest.h>

int A[80];
int N;
int bestscore[80][80][3];  // best score for the [i,j] sequence for each player, and the
                            // best move, 


int q;

void search(int i, int j, int *foo, int *bar) {

  char action;

  if (bestscore[i][j][2]) {
    *foo = bestscore[i][j][0];
    *bar = bestscore[i][j][1];
    return;
  }
  
  if (i==j) {
    *foo = A[i];
    *bar = 0;
    action = 'F';
  } else {
    int a,b,c,d,mybest_F,hisbest_F,mybest_L,hisbest_L;
    // try first
    search(i+1, j, &a, &b);  // a is the best score he could get, b is the best score I could get
    mybest_F = A[i] + b;
    hisbest_F = a;
    // try last
    search(i, j-1, &c, &d);
    mybest_L = A[j] + d;
    hisbest_L = c;
    if (mybest_F >= mybest_L) {
      *foo = mybest_F;
      *bar = hisbest_F;
      action = 'F';
    } else {
      *foo = mybest_L;
      *bar = hisbest_L;
      action = 'L';
    }
  }
  bestscore[i][j][0] = *foo;
  bestscore[i][j][1] = *bar;
  bestscore[i][j][2] = action;
}

int main(void) {
  int i,j,k,a,b;
  int dummy,dummy2;
  while ((1 == scanf("%d",&N)) && N) {
    static int game = 0;
    for (i=0; i<80; i++)                 // initialization
      for (j=0; j<80; j++) 
	for (k=0; k<3; k++)
	  bestscore[i][j][k] = 0;
    game ++;
    for (i=0; i<N; i++) scanf("%d",A+i);
    search(0,N-1,&dummy,&dummy2);
    printf("Game %d: ",game);
    a = 0; b = N-1;
    for (i=0; i<N; i++) {
      printf("%c", bestscore[a][b][2]);
      if (bestscore[a][b][2] == 'F') 
	a++;
      else
	b--;    
    }
    printf("\n\n");
  }
  return 0;
}
