#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int debug = 0;

/*
Kruskal's algorithm:
    sort the edges of G in increasing order by length
    keep a subgraph S of G, initially empty
    for each edge e in sorted order
        if the endpoints of e are disconnected in S
        add e to S
    return S
*/

typedef struct _place_t {
  char *name;
  int n_l;
  int *l;
  int reachable;
} place_t;

typedef struct _edge_t {
  int vertex_a;
  int vertex_b;
  int weight;
  int available;
} edge_t;

int n_p;
place_t *p;
int n_e;
edge_t *e;

int get_place(char *name) {
  int i;
  if (debug)
    printf("add_edge('%s')\n",name);
  for (i=0; i<n_p; i++) 
    if (!strcmp(name,p[i].name))
      return i;
  n_p ++;
  p = realloc(p, n_p * sizeof(place_t));
  p[n_p - 1].name = strdup(name);
  p[n_p - 1].reachable = 0;
  return (n_p - 1);
}

int add_edge(int a, int b, int weight) {
  if (debug)
    printf("add_edge(%d,%d,%d)\n",a,b,weight);
  n_e ++;
  e = realloc(e, n_e * sizeof(edge_t));
  e[n_e - 1].vertex_a = a;
  e[n_e - 1].vertex_b = b;
  e[n_e - 1].weight = weight;
  return (n_e - 1);
}

int edge_compare(edge_t *a, edge_t *b) {
  if (a->weight > b->weight)
    return 1;
  else
    if (a->weight < b->weight)
      return -1;
  return 0;
}

int main(int argc, char **argv) {
  char buffer[255];
  char buffer2[255];
  int weight;
  int place_a, place_b;
  int i;

  p = 0;
  n_p = 0;
  e = 0;
  n_e = 0;
 
  while (1 == scanf("%s",buffer)) {
    
    if (!strcmp(buffer,";"))
      break;
    scanf("%s",buffer2);
    scanf("%i",&weight);

    place_a = get_place(buffer);
    place_b = get_place(buffer2);
    add_edge(place_a,place_b,weight);
  }

  qsort(e,n_e,sizeof(edge_t),edge_compare);
  
  for (i=0; i<n_e; i++) {
    printf("edge %u from %u to %u weight %u\n",
	   i,e[i].vertex_a,e[i].vertex_b,e[i].weight);
  }

  for (i=0; i<n_e; i++) {
    if (! p[e[i].vertex_a].reachable ) |
 (! p[e[i
  }
}




