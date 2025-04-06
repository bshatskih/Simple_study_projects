#include <iostream>
#include <vector>
#include <cstdint>
#include "Solution.h"

int main() {
  std::vector<int> test{1,2};
  Solution a;
  std::cout << a.maxArea(test);
  return 0;
}
