#include <iostream>
#include <algorithm>
#include <vector>
#include <ranges>
#include "Solution.h"

int unary_operation(int a) {
  if (a % 2 == 0) {
    return a * a;
  } else {
    return a + 2;
  }
}


int main() {
  Solution a;
  std::vector<int> u{1,2,3,4,5,6,7,8,9,10};
//  std::transform(u.begin(), u.end(), u.begin(),::unary_operation);
  std::ranges::copy(u, std::ostream_iterator<int>(std::cout, " "));
  return 0;
}
