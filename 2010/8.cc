#include "contest.h"

int x[100000];
int y[100000];

int main(int argc, char **argv) {
  int N = 0;

  while (cin >> x[N] >> y[N]) 
    N++;
 
  double best_extent = 0;
  for (double angle=0.0; angle<M_PI/2.0; angle+=5.0*M_PI/180.0) {
    double sina, cosa;
    int min_i = 0, max_i = 0;
    double max_x = -1.0/0.0;  // -Infinity
    double min_x =  1.0/0.0;  // +Infinity
    sincos(angle, &sina, &cosa);
    
    /* Find the extremal points after rotation by the angle */
    for (int i=0; i<N; i++) {
      double xprime = cosa*x[i] + sina*y[i];
      if (xprime > max_x) {
	max_x = xprime;
	max_i = i;
      }
      if (xprime < min_x) {
	min_x = xprime;
	min_i = i;
      }
    }
    /* See how far apart they are */
    if ((max_x - min_x) > best_extent) {
      best_extent = (max_x - min_x);
      best_i = max_i;
      best_j = min_i;
    }
  }
  /* best_extent now contains an estimate of the set diameter which is
     guaranteed to be good to the desired accuracy.  However, because
     we have kept track of the points that resulted in this estimate
     of the separation, we can improve our estimate by explicitly
     calculating the distance between these points. 
  */
  printf("%1.1f\n", sqrt( (x[max_i]-x[min_i])*(x[max_i]-x[min_i]) +
			  (y[max_i]-y[min_i])*(y[max_i]-y[min_i])));
  return 0; 
}
	 
