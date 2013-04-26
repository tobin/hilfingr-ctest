#include <contest.h>

int main(int argc, char **argv) {
  
  vector<int> data;
  double sum = 0;
  int n = 0;
  int x;
  while (cin >> x) {
    data.push_back(x);
    sum += x;
    n ++;
  }
  double mean = sum / n;

  sort(data.begin(), data.end());

  // find the first element greater than or equal to the mean
  auto i = data.begin();
  while (*i < mean) i++;
  
  if (*i == mean) 
    cout << *i << endl;
  else {
    double d1 = mean - *(i-1);  // distance to element below the mean
    double d2 = *i - mean;      // distance to element above the mean
    if (d1 == d2)
      cout << *(i-1) << " " << (*i) << endl;
    else
      cout << (d1 < d2 ? *(i-1) : *i ) << endl;
  }

  return 0;
	
}
