#include <contest.h>

#define D if (1)
const double inf = 1.0/0.0;
typedef pair<double,double> coord;

double diameter(vector<coord> coords) {
  double max_diameter = -inf;

  for (double angle=0; angle <= M_PI/2; angle += M_PI/180.0) {
    
    // find the min and max x-coordinate in this orientation
    double min =  inf;
    double max = -inf;
    vector<coord>::iterator min_i, max_i;

    for (auto i=coords.begin(); i < coords.end(); i++) {
      double x = i->first*cos(angle) - i->second*sin(angle);
      if (x < min) {
	min = x;
	min_i = i;
      }
      if (x > max) {
	max = x;
	max_i = i;
      }
    }
    double diameter = sqrt(pow(max_i->first - min_i->first, 2) + 
			   pow(max_i->second - min_i->second, 2));


    if (diameter > max_diameter) 
      max_diameter = diameter;
  }
  return max_diameter;
}


int main(int argc, char **argv) {  
  string s;
  int m = 0; 

  while (getline(cin, s)) {
    cout << "Set #" << ++m << ": ";
    
    double x, y;
    vector<coord> coords;
    stringstream ss(s);
    while (ss >> x >> y)  
      coords.push_back(coord(x,y));
    
    cout << setiosflags(ios::fixed) << setprecision(2);
    cout << "Diameter is " << diameter(coords) << endl;
  }  
  return 0;
}
