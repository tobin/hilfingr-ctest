#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* 
This program returns the distance between two cells in a honeycomb,
where the cells are indexed in a sort of spiral around cell #1.

                    17     18  19   20
                 16     6     7   8     21
              15     5     1    2    9   22
                 14     4    3    10   23
              29    13    12    11  24     

The program works by first converting the cell number into coordinates
(x,y,z) and then using the honeycomb distance formula d = max { |dx|,
|dy|, |dz|x}.

Tobin Fricke - 2012-10-03
*/


#define D if (0)

int max(int a, int b, int c) {
  int foo = a > b ? a : b;
  return foo > c ? foo : c;
}

// return the nth centered hexagonal number
int hexno(int n) {
  return n<0 ? 0 : 1 + 3*n*(n+1);
}

int hexlog(int n) {
  int i = 0;
  while (hexno(i) < n) // FIXME: Make this closed form.
    i++;
  return i;
}

void cell2coord(int n, int *x, int *y, int *z) {
  /* Identify which "ring" this cell lies on.
     ring 0 = cell 1
     ring 1 = cells 2, 3, 4, 5, 6, 7
     ring 2 = cells 8 .. 19 */

  int ring = hexlog(n);

  /* The 0th ring contains 1 cell, but all other
     rings R contain 6*R cells. */

  int remainder = n - hexno(ring-1);
  int side = ring == 0 ? 0 : remainder / (ring );
  int index = ring == 0 ? 0 : remainder % (ring );
  
  switch (side) {
  case 0:
  case 6:  // handle cells 7, 19, 37, ...
    *x = index;
    *y = ring - index;
    *z = -ring;
    break;
  case 1:
    *x = ring;
    *y = - index;
    *z = index - ring;
    break;
  case 2:
    *x = ring - index;
    *y = -ring;
    *z = index;
    break;
  case 3:
    *x = - index;
    *y = index - ring;
    *z = ring;
    break;
  case 4:
    *x = -ring;
    *y = index;
    *z = ring - index;
    break;
  case 5:
    *x = -ring + index;
    *y = ring;
    *z = -index;
    break;
  }
  D printf("%d --> (%d, %d, %d)\n", n, *x, *y, *z);
  assert(*x + *y + *z == 0);
  return;
}

int honeycomb_distance(int a, int b) {  
  int x1, y1, z1, x2, y2, z2;

  // first convert to "honeycomb coordinates"...
  cell2coord(a, &x1, &y1, &z1);
  cell2coord(b, &x2, &y2, &z2);

  // and then use the honeycomb distance formula.
  return max(abs(x2 - x1), abs(y2 - y1), abs(z2 - z1));
}


int main(int argc, char**argv) {
  int a, b;
  assert(honeycomb_distance(19,30)==5);
  while (2==scanf("%d %d", &a, &b) && (a>0) && (b>0)) 
        printf("The distance between cells %d and %d is %d.\n", 
	a, b, honeycomb_distance(a,b)); 
  return 0;
}
