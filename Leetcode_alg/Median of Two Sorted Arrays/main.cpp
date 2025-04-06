#include <iostream>
#include <vector>
#include "Solution.h"

int main() {
  std::vector<int> a({1, 2, 6, 7});
  std::vector<int> b({10, 22, 23, 25, 99, 101, 110, 111});
  Solution res;
  std::cout << res.findMedianSortedArrays(a,b);
  return 0;
}
