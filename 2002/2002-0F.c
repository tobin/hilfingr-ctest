#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define D if (1) 

double R = 16.7/2.0;  // planet radius

/* convert spherical coordinates to cartesian coordinates */

void spherical_to_cartesian(double r, double theta, double phi, double v[]) {
  v[0] = r*cos(theta)*sin(phi);
  v[1] = r*sin(theta)*sin(phi);
  v[2] = r*cos(phi);
}

/* compute the dot product of two N-dimensional vectors */

double dot(double A[], double B[], int N) {  
  double sum = 0;
  while (N--) 
    sum+=A[N]*B[N];
   return sum;
}

/* convert degrees to radians */

double deg2rad(double theta) {
  return theta*M_PI/180.0;
}

/* compute spherical distance */

double arc_dist(double lat0, double lon0, double lat1, double lon1) {
  double v[2][3];
  spherical_to_cartesian(R,lon0,lat0,v[0]);
  spherical_to_cartesian(R,lon1,lat1,v[1]);
  return acos(dot(v[0],v[1],3)/sqrt(dot(v[0],v[0],3)*dot(v[1],v[1],3)));
}

struct _edge {
  int i;           // from
  int j;           // to
  double len;      // length
};

int edge_compare(struct _edge *e1, struct _edge *e2) {
  double z = e1->len - e2->len;
  return (z == 0 ? 0 : (z < 0 ? -1 : 1));
}

int main(void) {
  int N;
  while (1==scanf("%d",&N) && N>0) {

    static int dataset = 0;
    double total_dist = 0;
    dataset ++;

    D printf("\n=== Case %d ======================\n",dataset);

    double lat[N], lon[N];
    
    for (int i=0; i<N; i++) {
      scanf("%lf %lf",&(lat[i]),&(lon[i]));
      lat[i] = deg2rad(90-lat[i]);
      lon[i] = deg2rad(lon[i]);
      D { 
	double v[3];
	spherical_to_cartesian(1,lon[i],lat[i],v);
	printf("Point %d: lat %7.2f, lon %7.2f  (%0.3f, %0.3f, %0.3f)\n",
	       i,90 - 180*lat[i]/M_PI,180*lon[i]/M_PI,v[0],v[1],v[2]);
      }

    }
    
    /* compute pairwise distances */

    struct _edge edges[N*(N-1)/2];
    int n_edges = 0;    
    for (int i=0; i<N; i++)
      for (int j=i+1; j<N; j++) {	
	edges[n_edges].i = i;
	edges[n_edges].j = j;
	edges[n_edges].len = arc_dist(lat[i],lon[i],lat[j],lon[j]);
	n_edges ++;
      }

    qsort(edges, n_edges, sizeof(struct _edge), edge_compare);

    D {
      printf("There are %d edges: \n", n_edges);
      for (int i=0; i<n_edges; i++)
	printf("%2d --> %2d, length %6.2f\n",
	       edges[i].i, edges[i].j, 180*edges[i].len/M_PI);
    }

    int class[n_edges], rank[n_edges];

    for (int i=0; i<n_edges; i++) {
      class[i] = i;                
      rank[i] = 0;
    }

    int FindSet(int x) {
      if (x != class[x])
	class[x] = FindSet(class[x]); 
      return class[x];
    }

    void Union(int x, int y) {
      x = FindSet(x);
      y = FindSet(y);
      if (rank[x] > rank[y])
	class[y] = x;
      else {
	class[x] = y;
	if (rank[x] == rank[y])
	  rank[y] ++;
      }
    }
    
    for (int k=0; k<n_edges; k++) {
      if (FindSet(edges[k].i) != FindSet(edges[k].j)) {
	D printf("Connect points %d and %d\n",edges[k].i,edges[k].j);
	Union(edges[k].i,edges[k].j);
	total_dist += edges[k].len;
      }
    }
    printf("Case %d: %2.2f miles\n",dataset,R*total_dist);
  }
}
