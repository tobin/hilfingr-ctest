#include <stdio.h>
#include <stdlib.h>

/* Tobin Fricke
   August 7, 2000
*/

#define D if (0)

typedef struct _node_t {
  int type;
  char val;
  struct _node_t *left, *right;
} node_t;

char **chars;
int n_chars;

void add_char(char c, int n) {
 int i;
 D printf("add_char(%c,%u)\n",c,n);
 if (n_chars < n+1) {
  chars = (char **)realloc(chars, (n+1) * sizeof(char *));
  for (i=n_chars; i<n+1; i++) 
   chars[i] = (char *)NULL;
  n_chars = n+1;
 }

 if (chars[n]==NULL) 
  chars[n] = (char *)calloc(1024, sizeof(char));

 chars[n][strlen(chars[n])] = c;
}

node_t *new_node(node_t *left, node_t *right) {
 node_t *node;
 D printf("new_node(left,right)\n");
 node = (node_t *)calloc(1,sizeof(node_t));
 node->type = 1;
 node->left = left;
 node->right = right;
 return node;
}

node_t *new_leaf(char c) {
 node_t *node;
 D printf("new_leaf('%c')\n",c);
 node = (node_t *)calloc(1,sizeof(node_t));
 node->type = 0;
 node->val = c;
 return node;
}

node_t *make_tree(int depth) {
 D printf("make_tree(%u)\n",depth);

 if (n_chars - 1 > depth)  {
  node_t *left, *right;
  left = make_tree(depth+1);
  right = make_tree(depth+1);
  return new_node(left,right);
 }

 if (n_chars - 1 == depth) {
  char c;
  node_t *node;
  c = chars[n_chars - 1][0];
  node = new_leaf(c);
  chars[n_chars - 1] ++;
  while ((n_chars>0) && ((chars[n_chars - 1] == NULL) || (chars[n_chars - 1][0] == 0))) n_chars --;
  return node;
 }

 printf("Invalid input\n");
 exit(0); 
}

void tree_str(node_t *node) {
 if (node->type == 0) 
  printf("%c",node->val);
 else {
  printf("(");
  tree_str(node->left);
  printf(",");
  tree_str(node->right);
  printf(")");
 }
}

int tree_find(node_t *node, char c, char *prefix) {
 if (node->type == 1) {
   char buffer[1024];
   strcpy(buffer, prefix);
   strcat(buffer, "0");
   if (tree_find(node->left, c, buffer)) return 1;
 
   strcpy(buffer, prefix);
   strcat(buffer, "1");
   if (tree_find(node->right, c, buffer)) return 1;

 } else 

   if (node->val == c) {
      printf("%s\n",prefix);
      return 1;
   }

 return 0;
}


int main() {
 char c;
 int n,i;
 node_t *tree;
 char *buffer;

 chars = (char **)NULL;
 n_chars = 0;
 buffer = (char *)calloc(1024,sizeof(char));

 while (2 == scanf(" %c %u",&c,&n)) {
  add_char(c,n);
  buffer[strlen(buffer)] = c;
 }

 D for(i=0; i<n_chars; i++) 
  printf("%u: %s\n",i,chars[i]);

 tree = make_tree(0);

 while (buffer[0] != 0) {
  printf("%c ",buffer[0]);
  tree_find(tree,buffer[0],"");
  buffer++;
 }
}
