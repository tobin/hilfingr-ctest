#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
 
int edges[101][101], in_path[101];
#define min(a,b) (a<b?a:b)
#define Infinity ((1 << 31) - 1)

int search(int nodes, int start, int finish, int amount) {
  int total_transferred = 0, i;
   if (start == finish) 
     return amount;
  for (i=1; i<=nodes; i++) {
    if ((!in_path[i]) && (edges[start][i] > 0)) {
      int amount_attempted = 0, amount_transferred = 0;
      in_path[i] = 1;
      amount_attempted = min(edges[start][i],amount);
      edges[start][i] -= amount_attempted;
      edges[i][start] += amount_attempted;
      amount_transferred = search(nodes, i,finish,amount_attempted);
      edges[start][i] += amount_attempted - amount_transferred;
      edges[i][start] -= amount_attempted - amount_transferred;
      in_path[i] = 0;
      total_transferred += amount_transferred; 
      amount -= amount_transferred;
      if (!amount) break;
    }
  }
  return total_transferred;
}

int main(int argc, char **argv) {
  int a,b,z,n,s,t,c,i,bandwidth, networks=0;
  while ((4 == scanf("%d %d %d %d",&n,&s,&t,&c)) && n) {
    bzero(edges,101*101*sizeof(int));
    bzero(in_path,101*sizeof(int)); 
    in_path[s] = 1;  /* The start node is always in the path. */
    for (i=0; i<c; i++) {
      scanf("%d %d %d",&a, &b, &z);
      edges[b][a] = edges[a][b] = (edges[a][b] + z);
    }
    bandwidth = search(n,s,t,Infinity);
    printf("Network %d\nThe bandwidth is %d.\n",++networks,bandwidth);
  }
  return 0;
}



