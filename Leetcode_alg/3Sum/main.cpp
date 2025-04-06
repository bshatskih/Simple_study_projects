#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include "Solution.h"

int main() {
  std::clock_t start = clock();
  Solution a;
  std::vector<int> g = {-1,0,1,2,-1,-4};
  std::vector<std::vector<int>> res = a.threeSum(g);
  for (std::vector<int> &i : res) {
    std::cout << i[0] << ", " << i[1] << ", " << i[2] << '\n';
  }
  std::clock_t end = clock();
  std::cout << "Time: " << (end - start)/1000;
  return 0;
}
