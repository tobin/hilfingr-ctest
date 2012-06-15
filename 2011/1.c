#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_LABELS 2000
const int R = 40;
const int C = 40;

int max(int x, int y) {
  return x > y ? x : y;
}

void swap_int(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

int n_labels = 0;
int relabeling[MAX_LABELS];

int find(int x) {
  while (relabeling[x] != x)
    x = relabeling[x];
  return x;
}

int combine(int x, int y) {
  x = find(x);
  y = find(y);
  if (x == y) return x;

  if (x > y) swap_int(&x, &y);

  relabeling[y] = x;
  return x;
}

int new_label() {
  n_labels ++;
  relabeling[n_labels] = n_labels;
  return n_labels;
}

int relabel(char matrix[R][C], int labels[R][C], int rows, int cols) {

  for (int row=0; row<rows; row++)
    for (int col=0; col<cols; col++) {
      char my_symbol = matrix[row][col];
      int my_label = 0;
      for (int dir=0; dir<2; dir++) {
	char neighbor_symbol;
	char neighbor_label;
	switch (dir) {
	case 0:  // up
	  if (row==0) continue;
	  neighbor_symbol = matrix[row-1][col];
	  neighbor_label  = labels[row-1][col];
	  break;
	case 1: // left
	  if (col==0) continue;
	  neighbor_symbol = matrix[row][col-1];
	  neighbor_label  = labels[row][col-1];
	  break;
	default:
	  assert(0);
	}
	if (my_symbol == neighbor_symbol) {
	  if (!my_label) 
	    my_label = neighbor_label;
	  else // already assigned
	    my_label = combine(my_label, neighbor_label);	
	} 
      } // directions
      if (!my_label)
	my_label = new_label();
      labels[row][col] = my_label;
    } // matrix scan

  // fix up the labels

  int max_label = 0;
  for (int row=0; row<rows; row++)
    for (int col=0; col<cols; col++) {
      labels[row][col] = find(labels[row][col]);
      max_label = max(max_label, labels[row][col]);
    }
  
  return max_label;
}


int main(int argc, char **argv) {
  char str[R][C];
  int labels[R][C];
  while (1==scanf("%s", str[0])) {
    int len = strlen(str[0]);
    for (int i=1; i<len; i++) 
      scanf("%s", str[i]);
    printf("-----\n");
    assert(len<=R && len<=C);

    relabel(str,labels,len,len);

    for (int row=0; row<len; row++) {
      printf("%s ", str[row]);
      for (int col=0; col<len; col++) 
	printf(" %02x", labels[row][col]);
      printf("\n");
    } 
  }
  return 0;
}
