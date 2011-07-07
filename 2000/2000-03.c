
#include <contest.h>

typedef struct _point_t {
  double x;
  double y;
  struct _point_t *next;
} point_t;



point_t *new_point(double x, double y, point_t *next) {
  point_t *point;
  point = (point_t *)malloc(sizeof(point_t));
  point->x = x;
  point->y = y;
  point->next = next;
  return point;
}


void iterate(point_t *point) {

  point_t *midpoint;
  double  length,d_x,d_y, op,ad,hy,nd_x,nd_y;

  while (point->next != NULL) {

    length = sqrt (pow( point->next->x - point->x, 2.0) +
		   pow( point->next->y - point->y, 2.0));

    
    hy = length;
    
    op = point->next->y - point->y;
    ad = point->next->x - point->x;
   

    d_x = length/2.0;
    d_y = length/2.0;

    /* now we need to rotate counterclockwise */
    
    nd_y =   d_x * (ad/hy) + d_y * (op/hy);   /* x = x * cos + y * sin */
    nd_x = - d_x * (op/hy) + d_y * (ad/hy);
    
    midpoint = new_point(point->x + nd_x, point->y + nd_y, point->next);

    point->next = midpoint;
    point = point->next->next;

  }

}


int main(int argc, char **argv) {
  
  double x0, y0, x1, y1;
  int i, iterations;
  point_t *point;

  while (5 == scanf("%lf %lf %lf %lf %u",
		    &x0, &y0, &x1, &y1, &iterations)) {

    point = new_point(x0,y0, new_point(x1,y1, (point_t *)NULL));
    
    for (i=0; i<iterations; i++) {
      iterate(point);
    }
    
    while (point->next != NULL) {
      point_t *temp;
          printf("%0.5e %0.5e %0.5e %0.5e v\n",  

      /*        printf("%lf %lf %lf %lf v\n",*/
	     point->x, point->y,
	     point->next->x, point->next->y);
      temp = point;
      point = point->next;
      /* free(temp); */
    }

    
    printf("done\n");
  }
  return 0;
}



