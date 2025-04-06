#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "Solution.h"

int main() {
  Solution d;
  std::vector<int> a{1, 2, 3};
  std::cout << d.combinationSum4(a, 4);
  return 0;
}
