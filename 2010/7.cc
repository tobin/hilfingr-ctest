#include "contest.h"
#include <assert.h>

int main(int argc, char **argv) {
  int rows, cols;
  cin >> rows >> cols;
  int nodes = rows*cols;

  int R;
  // matrix of conductances between nodes
  double S[nodes][nodes];
  
  for (int i=0; i<nodes; i++)
    for (int j=0; j<nodes; j++)
      S[i][j] = 0;

  // read 2 M N - M - N resistors

  for (int row=0; row<rows; row++) {
    // read the 'horizontal' resistors
    //    cout << "reading horizontal" << endl;
    for (int col=0; col<(cols-1); col++) {
      int from_node = row*cols + col;
      int to_node   = row*cols + (col+1);
      assert(from_node < to_node);
      cin >> R;
      //      cout << "Got " << R << " Ohms from " << from_node << " to " << to_node << endl;
      S[from_node][to_node] = 1.0/R;
    }
    if (row == rows-1)
      break;
    //    cout << "reading vertical" << endl;
    // read the 'vertical' resistors
    for (int col=0; col<cols; col++) {
      int from_node =     row*cols + col;
      int to_node   = (row+1)*cols + col;
      assert(from_node < to_node);
      cin >> R;
      //      cout << "Got " << R << " Ohms from " << from_node << " to " << to_node << endl;
      S[from_node][to_node] = 1.0/R;
    }
  }
  
  //  cout << "Adjacency matrix is:" << endl;
  /*  for (int i=0; i<nodes; i++)
    for (int j=0; j<nodes; j++)
      if (S[i][j] != 0)
	printf("R(%d,%d) = %f\n", i,j,1.0/S[i][j]);
  */
  int N = nodes;
  double matrix[N][N];
  for (int i=0; i<N; i++) 
    for (int j=0; j<N; j++)
      matrix[i][j]=0;
  

  // Stick this into a matrix to be inverted
  for (int i=0; i<nodes; i++) {
    // write the node equation for currents into node i
    for (int j=0; j<nodes; j++) {
      // another (Vx - Vy) / Rxy 
      matrix[i][i] += S[i][j] + S[j][i];  
      matrix[i][j] -= S[i][j] + S[j][i];  
    }
    
  }

  // Lump the last node in with the ground node
  int node_gnd = cols*(rows - 1);
  int node_1v  = cols*rows - 1;
  
  for (int j=0; j<N; j++) {
    matrix[node_gnd][j] -= matrix[node_1v][j];
    matrix[node_1v][j]  = 0;
  }

  // Stick in an equation for the voltage source
  matrix[node_1v][node_1v]  =  1;
  matrix[node_1v][node_gnd] = -1;
  
  // Solve!
  double A[(N-1)*(N-1)];
  double b[N], x[N];
  for (int i=0; i<N; i++) b[i] = 0.0;
  b[N-2] = 1.0;

  //  cout << "Matrix to solve is: " << endl;
  // copy into the matrix (dumb)
  for (int r=0; r<N; r++) {
    for (int c=0; c<N; c++) {
      int rp = (r > node_gnd) ? r - 1 : r;
      int cp = (c > node_gnd) ? c - 1 : c;
      A[rp*(N-1)+cp] = matrix[r][c];
    }
  }
  linearSolve (N-1, A, b, x);

  // Print out the results

  //  cout << "Solution is:" << endl;
  int j=0;
  for (int i=0; i<N; i++) {
    if (i == node_gnd) 
      printf("%2.2f ", 0.0);
    else
      printf("%2.2f ", x[j++]);
    if ((i+1)%cols == 0)
      printf("\n");
  }
  
  
  return 0;
}
