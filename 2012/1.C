
#include <iostream>
#include <unordered_map>
#include <string>

#define D if (0)

const int int_inf = 2000000000;

using namespace std;
typedef unordered_map<string, int> Map;

int max_distance(int w[100][100], int n) {
  // n = number of cities
  // n : <city,city> --> distance  encodes the roads
  int d[n][n];

  // initialization
  for (int i=0; i<n; i++) 
    for (int j=0; j<n; j++) 
      d[i][j] = w[i][j];

  for (int i=0; i<n; i++) 
    for (int j=0; j<n; j++) 
      D cout << "Directly: City " << i << " to city " << j << " is " << d[i][j] << " miles." << endl;
      
  // floyd-warshall
  for (int k=0; k<n; k++) 
    for (int i=0; i<n; i++) 
      for (int j=0; j<n; j++) 
	if ((d[i][k] != int_inf) && (d[k][j] != int_inf) && (d[i][k] + d[k][j] < d[i][j])) {
	  d[i][j] = d[i][k] + d[k][j];
	  d[j][i] = d[i][j];
	}
	  

  // now find the maximum
  int max = 0;
  for (int i=0; i<n; i++) 
    for (int j=0; j<n; j++) {
      D cout << "City " << i << " to city " << j << " is " << d[i][j] << " miles." << endl;
      max = (d[i][j] > max ? d[i][j] : max);
    }

  
  return max;
}

int main(int argc, char **argv) {

  int n_roads;  
  int n = 0;
  while (cin >> n_roads) {
    if (!n_roads) break;
    Map cities;
    int roads[100][100];

    for (int i=0; i<100; i++) 
      for (int j=0; j<100; j++) 
	roads[i][j] = (i==j ? 0 : int_inf); // infinity
    
    int n_cities = 0;
    for (int i=0; i<n_roads; i++) {
      string city1, city2;
      int distance;
      cin >> city1 >> city2 >> distance;

      if (cities.find(city1) == cities.end())
	cities[city1] = n_cities++;
      if (cities.find(city2) == cities.end())
	cities[city2] = n_cities++;

      int x = cities[city1];
      int y = cities[city2];

      roads[x][y] = distance;
      roads[y][x] = distance;
      D cout << "City " << x << " to city " << y << " is " << distance << " miles" << endl;
    }
    D cout << "There are " << n_cities << " cities." << endl;
    cout << "Set #" << ++n << ": " << max_distance(roads, n_cities) << endl;
  
  }
  return 0;
}
