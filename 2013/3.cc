// Tobin Fricke 2013-10-05
#include <iostream>

using namespace std;

#define D if (0)

int main(int argc, char **argv) {
  int N;
  while (cin >> N) {
    D cout << "--------------------------------" << endl;
    int table[N+1][N];
    for (int i=0; i<N; i++) 
      cin >> table[i][0];
    
    // Calculate the difference table
    for (int j=1; j<N; j++)  // column
      for (int i=j; i<N; i++) // row
	table[i][j] = table[i][j-1] - table[i-1][j-1];
    
    // Print out the difference table, for checking
    D for (int i=0; i<N; i++) { // row
      for (int j=0; j<=i; j++)   // column
	cout << " " << table[i][j];
      cout << endl;
    }
    
    int K;
    cin >> K;

    // copy the last row of the table
    for (int j=0; j<N; j++)
      table[N][j] = table[N-1][j];

    for (int k=N; k<K; k++) {
      // update the table
      for (int j=(N-2); j>=0; j--)
	table[N][j] += table[N][j+1];
      // print it out
      for (int j=0; j<(N-1); j++) 
	D cout << " " << table[N][j];
      D cout << endl;
    }

    cout << "Term " << K << " of the sequence is ";
    cout << (K<=N ? table[K-1][0] : table[N][0]) << endl;
  }

}
