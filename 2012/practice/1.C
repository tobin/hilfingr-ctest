#include <contest.h>

int int_compare(const void *a, const void *b) {
  return (*(int *)a - *(int *)b);
}

int main(int argc, char **argv) {

  double sum = 0;
  int max_n = 1;
  int *arr = (int *)calloc(max_n, sizeof *arr);
  int n = 0;

  // read input
  int x;
  while (scanf("%d", &x)==1) {
    n++;
    if (n > max_n) {
      max_n *= 2;
      arr = (int *)realloc(arr, max_n * sizeof *arr);
    }
    arr[n-1] = x;
    sum += x;
  }
  double mean = sum / n;

  qsort(arr, n, sizeof *arr, int_compare);

  // binary search
  int p = 0;
  int q = n-1;
  int c;

  while (c = p + (q-p)/2, q-p > 1 ) 
    if (arr[c] > mean)   // found item is too big
      q = c;             // found item is an upper bound
    else 
      p = c;

  
  // probably not the most elegant
  if (arr[p] == arr[q])
    printf("%d\n", arr[p]);
  else
    if ( mean - arr[p] == arr[q] - mean) 
      printf("%d %d\n", arr[p], arr[q]);
    else
      if (mean - arr[p] < arr[q] - mean)
	printf("%d\n", arr[p]);
      else
	printf("%d\n", arr[q]);
  
  return 0;
	
}
