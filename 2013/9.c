// Tobin Fricke 2013-10-05

#include <stdio.h>
#include <stdlib.h>

#define D if (0)

struct node {
  int L;
  int n_children;
  double x;
  double min_x, max_x;
  struct node **children;
};

struct node *read_tree() {
  struct node *me = (struct node *)calloc(1, sizeof(struct node));

  if (scanf("%d %d", &me->n_children, &me->L) != 2) {
    free(me);
    return 0;
  }

  me->children = (struct node **)calloc(sizeof(struct node *), me->n_children);
  me->x = 0;

  for (int n=0; n<me->n_children; n++) 
    me->children[n] = read_tree();

  return me;
}

void print_tree(struct node *tree) {
  printf("   %d %0.4f\n", tree->L, tree->x);
  for (int i=0; i < tree->n_children; i++) 
    print_tree(tree->children[i]);
}

// calculate positions, return next available x position to the right
double calc_pos(struct node *tree, double offset, int depth) {
  D for (int i=0; i<depth; i++) printf(" ");
  D printf("calc_pos(%d, %lf)\n",tree->L, offset);

  tree->x = offset;

  // first ask the children to figure out how big they are
  for (int i=0; i < tree->n_children; i++) {
    if (i>0) offset++;
    offset = calc_pos(tree->children[i], offset, depth+1);
  }

  // "Any inner node is positioned half way between its leftmost and
  // rightmost (immediate) child."
  if (tree->n_children > 0) {
    double x1 = tree->children[0]->x;
    double x2 = tree->children[tree->n_children-1]->x;
    //    D for (int i=0; i<depth+1; i++) cout << " ";
    //D cout << "My children have positions " << x1 << " and " << x2 << endl;
    tree->x = (x1+x2)/2.0; 
  } 

  D for (int i=0; i<depth+1; i++) printf(" ");
  D printf("Node %d has x = %lf\n", tree->L, tree->x);

  return offset;
}


int main(int argc, char **argv) {
  struct node *tree;
  int n = 0;
  while ((tree = read_tree())) {
    printf("Tree %d:\n", ++n);
    calc_pos(tree, 0, 0);
    print_tree(tree);
  }
  return 0; 
}
