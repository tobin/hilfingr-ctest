#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int debug = 0;

typedef struct _file_t {
  char *filename;
  int n_d;  /* number of defined symbols */
  int n_u;  /* number of undefined symbols */
  char **d; /* defined symbols */
  char **u; /* undefined symbols */
  int used;
} file_t;


typedef struct _pair_t {
  char *symbol;
  file_t *file;
} pair_t;

int n_p;
pair_t *p;

void hash_put(char *symbol, file_t *file) {
  /* we're guaranteed that a given symbol will only be defined once */
  pair_t pair;
  pair.symbol = strdup(symbol);
  pair.file = file;
  n_p ++;
  p = realloc(p, sizeof(pair_t) * n_p);
  p[n_p - 1] = pair;
}

file_t *hash_get(char *symbol) {
  int i;
  for (i = 0; i<n_p; i++) 
    if (!strcmp(p[i].symbol,symbol))
      return p[i].file;
  return NULL;
}


int n_u;     /* number of symbols that still need to be defined */
char **u;    /* symbols that still need to be defined */

int n_f;
file_t **f;

int main(int argc, char **argv) {
  char buffer[255];
  int i,j;

  n_u = 0; u = 0;
  n_f = 0; f = 0;
  n_p = 0; p = 0;

  /* read in the root words */

  while (1) {
    scanf("%s",buffer);
    if (!strcmp(buffer,";"))
      break;

    n_u ++;
    u = realloc(u, n_u * sizeof(char *));
    u[n_u - 1] = strdup(buffer);
  }

  if (debug)
    for (i=0; i<n_u; i++)
      printf("root word %u: '%s'\n",i,u[i]);

  /* read in the files */

  while (1 == scanf("%s",buffer)) {
    file_t *bob;
    bob = malloc(sizeof(file_t));
    bob->filename = strdup(buffer);
    bob->n_u = 0; 
    bob->u = NULL;
    bob->n_d = 0;
    bob->d = NULL;
    bob->used = 0;
    if (debug)
      printf("creating file '%s':\n",bob->filename);
    while (scanf("%s",buffer)) {
      char buffer2[255];
      if (!strcmp(buffer,";"))
	break;
      scanf("%s",buffer2);
      if (buffer[0]=='D') {
	if (debug)
	  printf(" defines '%s'\n",buffer2);
	bob->n_d ++;
	bob->d = realloc(bob->d,bob->n_d * sizeof(char *));
	bob->d[bob->n_d - 1] = strdup(buffer2);
	hash_put(buffer2,bob);
      } else {
	if (debug)
	  printf(" uses '%s'\n",buffer2);
	bob->n_u ++;
	bob->u = realloc(bob->u,bob->n_u * sizeof(char *));
	bob->u[bob->n_u - 1] = strdup(buffer2);
      }
    }
    n_f ++;
    f = realloc(f, n_f * sizeof(file_t *));
    f[n_f - 1] = bob;
  }

  if (debug)
    printf("processing...\n");

  for (i = 0; i < n_u; i++) {
    file_t *bob;
    bob = hash_get(u[i]);
    if (debug)
      printf("'%s' is defined in '%s'\n",u[i],bob->filename);
    for (j = 0; j < bob->n_u; j++) { 
      if (debug)
	printf(" '%s' uses but does not define '%s'\n",bob->filename,bob->u[j]);
      if (!hash_get(bob->u[j])->used) {
	if (debug) 
	  printf("still undefined: %s\n",bob->u[j]);
	n_u ++;
	u = realloc(u, n_u * sizeof(char *));
	u[n_u - 1] = bob->u[j];
      }
    }
    bob->used = 1;
  }

  for (i = 0; i < n_f; i++) {
    if (debug)
      printf("file '%s' is %s used\n",f[i]->filename,(f[i]->used ? "" : "not"));
    else {
      if (f[i]->used) printf("%s\n",f[i]->filename);
    }
  }    

}
