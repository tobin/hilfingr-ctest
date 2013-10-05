// Tobin Fricke 2013-10-05

#include <iostream>
#include <iomanip>
#include <stdlib.h>

#define D if (0)
using namespace std;

struct node {
  int L;
  int n_children;
  double x;
  double min_x, max_x;
  struct node **children;
};

node *read_tree() {
  node *me = new node;

  if (!(cin >> me->n_children >> me->L)) {
    delete(me);
    return 0;
  }

  me->children = (node **)calloc(sizeof(node *), me->n_children);
  me->x = 0;

  for (int n=0; n<me->n_children; n++) 
    me->children[n] = read_tree();

  return me;
}

void print_tree(node *tree) {
  cout << "   " << tree->L << " " << fixed << setprecision(4) << tree->x << endl;
  for (int i=0; i < tree->n_children; i++) 
    print_tree(tree->children[i]);
}

// calculate positions, return next available x position to the right
double calc_pos(node *tree, double offset, int depth) {
  D for (int i=0; i<depth; i++) cout << " ";
  D cout << "calc_pos(" << tree->L << ", " << offset << ")" << endl;

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

  D for (int i=0; i<depth+1; i++) cout << " ";
  D cout << "Node " << tree->L << " has x = " << tree->x << endl;

  return offset;
}


int main(int argc, char **argv) {
  node *tree;
  int n = 0;
  while ((tree = read_tree())) {
    cout << "Tree " << ++n << ":" << endl;
    calc_pos(tree, 0, 0);
    print_tree(tree);
  }
  return 0; 
}
