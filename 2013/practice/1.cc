#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
  vector<int> nums;
  int x;
  double sum = 0;

  while (cin >> x) {
    nums.push_back(x);
    sum += x;  // FIXME: Danger of overflow or loss of precision!
  }
  
  double avg = sum / nums.size();

  sort(nums.begin(), nums.end());

  // Find the first number above the average
  int i = 0;
  while (nums[i] < avg) 
    i++;

  // Check above and below the partition
  double d1 = avg - nums[i-1];
  double d2 = nums[i] - avg;

  if (d1 == d2) 
    cout << nums[i-1] << " " << nums[i] << endl;
  else {
    if (d1 < d2) 
      cout << nums[i-1] << endl;
    else
      cout << nums[i] << endl;
  }
  
  return 0;
}
