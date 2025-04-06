#include <iostream>
#include <vector>
#include "exception"
#include "Solution.h"

int main() {
//  std::cout << -INT_MIN;
  std::cout << Solution::divide(-2147483648, -1) << std::endl;
  return 0;
}
