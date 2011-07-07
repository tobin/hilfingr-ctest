#include "contest.h"

int table[7];
int hand[7][7][2];
int pc[2];
int n;

int probe(int player) {
int i,j;
 if (pc[player] == n) return 1;
  for (i = 0; i < 7; i++) 
   for (j =0; j <= i; j++) {
	 if (hand[i][j][player] && table[i]) {
	   hand[i][j][player]--;
	   if (i == j) table[i] += 2;
	   else table[i]--, table[j]++;
	   pc[player]++;
	   if (probe(!player)) return 1;
	   pc[player]--;
	   hand[i][j][player]++;
	   if (i == j) table[i] -= 2;
	   else table[i]++, table[j]--;
	 }
	 if (i != j && hand[i][j][player] && table[j]) {
	   hand[i][j][player]--;
	   table[i]++, table[j]--;
	   pc[player]++;
	   if (probe(!player)) return 1;
	   pc[player]--;
	   hand[i][j][player]++;
	   table[i]--, table[j]++;
	 }
	}
 return 0;
}

int main() {
int i,j,a,b,t;

  scanf("%d",&n);
  for (j = 0; j < 2 ;j++)
  for (i = 0; i < n; i++) {
   scanf("%d %d", &a, &b);
   if (b > a) t = a, a = b, b = t;
   hand[a][b][j]++;
   }
   scanf("%d %d", &a, &b);
   table[a] = 1;
   table[b] = 1;
   if (a == b) table[a] += 2;

   printf("It is%s possible to play all bones\n", probe(0) ? "" : " not");

 return 0;
}

