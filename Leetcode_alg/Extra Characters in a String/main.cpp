#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_set>
#include "Solution.h"

int main() {
  Solution a;
  std::vector<std::string> dictionary{"diz","v","o","wmo"};
  std::cout << a.minExtraChar("dxbsxxw", dictionary);
  return 0;
}
