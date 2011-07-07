#include <contest.h>
#include "contest.h"
/*#define debug*/

typedef struct _window_t {
  int x0, y0; /* lower left */  
  int x1, y1; /* upper right */

  int ox0, ox1, oy0, oy1;
} window_t;


int n_w;      /* number of windows */
window_t *w;  /* array of windows */


int new_window(int x0, int y0, int x1, int y1) {
  n_w = n_w + 1;
  w = realloc(w, sizeof(window_t) * n_w);
  w[n_w - 1].x0 = x0;
  w[n_w - 1].y0 = y0;
  w[n_w - 1].x1 = x1;
  w[n_w - 1].y1 = y1;
  
  w[n_w - 1].ox0 = x0;
  w[n_w - 1].ox1 = x1; 
  w[n_w - 1].oy0 = y0;
  w[n_w - 1].oy1 = y1;
  

  return n_w - 1;
}


int main(int argc, char **argv) {
  int wx, hx, num, parent, dim,i;
  char placement[10];

  n_w = 0;
  w = NULL;

  scanf("%d %d",&wx,&hx);

  new_window(0,0,wx,hx);

  while (4 == scanf("%d %d %d %s",&num,&parent,&dim,placement)) {

#ifdef debug
    printf("window %d with parent %d, aligned %s, dim %d\n",
	   num,parent,placement,dim);
#endif
    num --;
    parent --;
    
    n_w ++;
    w = (window_t *)realloc(w,sizeof(window_t) * n_w);

    if (n_w != num+1) {
      printf("m_w = %u, num = %u\n",n_w,num);
    }

    w[num] = w[parent]; /* by default coordinates are the same */
 
    switch (placement[0]) {
    case 'T':
      w[num].y0    = w[parent].y1 - dim;
      w[parent].y1 = w[parent].y1 - dim;
      break;
    case 'B':
      w[num].y1    = w[parent].y0 + dim;
      w[parent].y0 = w[parent].y0 + dim;
      break;
    case 'L':
      w[num].x1 =    w[parent].x0 + dim;
      w[parent].x0 = w[parent].x0 + dim;
      break;
    case 'R':
      w[num].x0 =    w[parent].x1 - dim;
      w[parent].x1 = w[parent].x1 - dim;
      break;
    default:
      printf("horrible error\n");
    }

    w[num].ox0 = w[num].x0;
    w[num].ox1 = w[num].x1;
    w[num].oy0 = w[num].y0;
    w[num].oy1 = w[num].y1;

#ifdef debug
    printf("creating new window (%d) with (%d,%d), (%d,%d)\n",
	   num+1,w[num].x0,w[num].y0,w[num].x1,w[num].y1);
    printf("old window (%d) now has (%d,%d), (%d,%d)\n\n",
	   parent+1,w[parent].x0,w[parent].y0,w[parent].x1,w[parent].y1);
#endif
  }

  for (i=0; i<n_w; i++) {
    printf("%d. %dx%d @ (%d,%d)\n",i+1,
	   w[i].ox1 - w[i].ox0, 
	   w[i].oy1 - w[i].oy0,
	   w[i].ox0,
	   w[i].oy0);
  }

  free(w);
  return 0;
}


