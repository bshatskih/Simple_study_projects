#include <iostream>
#include <vector>
#include "Solution.h"

int main() {
  std::vector<int> ans = {1,3};
  Solution a;
  ans = a.searchRange(ans, 1);
  std::cout << ans[0] << ' ' << ans[1] << std::endl;
  return 0;
}
