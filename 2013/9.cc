// Tobin Fricke 2013-10-05

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>

#define D if (0)
using namespace std;

struct node {
  int L;
  int n_children;
  double x;
  node **children;
  void print();
  double calc(double, int);
};

// Read a tree from an input stream
istream& operator >>(istream &is, node &me) {
  
  if (!(is >> me.n_children >> me.L)) {
    return is;  // failure
  }

  me.children = new node*[me.n_children];
  me.x = 0;

  for (int n=0; n<me.n_children; n++) {
    me.children[n] = new node;
    is >> *me.children[n];
  }

  return is;
}

void node::print() {
  cout << "   " << this->L << " " << fixed << setprecision(4) << this->x << endl;
  for (int i=0; i < this->n_children; i++) 
    this->children[i]->print();
}

// calculate positions, return next available x position to the right
double node::calc(double offset = 0, int depth = 0) {
  D cout << string(depth, ' ') << "calc(" << this->L << ", " << offset << ")" << endl;

  this->x = offset;

  // first ask the children to figure out how big they are
  for (int i=0; i < this->n_children; i++) {
    if (i>0) offset++;
    offset = this->children[i]->calc(offset, depth+1);
  }

  // "Any inner node is positioned half way between its leftmost and
  // rightmost (immediate) child."
  if (this->n_children > 0) {
    double leftmost = this->children[0]->x;
    double rightmost = this->children[this->n_children-1]->x;
    this->x = (leftmost+rightmost)/2.0; 
  } 

  D cout << string(depth+1, ' ') << "Node " << this->L << " has x = " << this->x << endl;

  return offset;
}


int main(int argc, char **argv) {
  node *tree = new node;
  int n = 0;
  while (cin >> *tree) {
    cout << "Tree " << ++n << ":" << endl;
    tree->calc();
    tree->print();
  }
  return 0; 
}
