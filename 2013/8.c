// Tobin Fricke
// 2013-10-05

#include <stdio.h>
#include <math.h>

#define D if (0)

int main(int argc, char **argv) {
  
  double w, theta1a, theta2a, theta1b, theta2b;
  int n = 0;
  while (scanf("%lf %lf %lf %lf %lf",
	       &w, &theta1a, &theta2a, &theta1b, &theta2b) == 5) {

    D printf("\nCase %d:\n", ++n);
    double t1_a = tan(theta1a * M_PI/180.0);
    double t2_a = tan(theta2a * M_PI/180.0);
    double z_a = w / (t1_a - t2_a);
    double x_a = z_a * t1_a;

    double t1_b = tan(theta1b * M_PI/180.0);
    double t2_b = tan(theta2b * M_PI/180.0);
    double z_b = w / (t1_b - t2_b);
    double x_b = z_b * t1_b;

    double dz = z_a - z_b;   // closing velocity, meters/second
    double dx = x_b - x_a;   // transverse velocity
    double dt = 1.0;         // time between measurements

    double vz = dz/dt;
    double vx = dx/dt;

    double t_impact = z_a / vz;
    double x_impact = x_a + vx * t_impact;

    D printf(" z_a = %lf, x_a = %lf \n", z_a, x_a);
    D printf(" z_b = %lf, x_b = %lf \n", z_b, x_b);
    
    if (vz > 0) {
      printf("Intersects at x=%0.2lf, t=%0.2lf\n", 
	     x_impact, t_impact);
    } else {
      printf("Not approaching\n");
    }


  }

  return 0;
}
