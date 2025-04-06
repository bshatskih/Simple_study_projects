#include <iostream>
#include <vector>
#include "Solution.h"

int main() {
  Solution a;
  std::vector<std::vector<int>> o{{2,5,8},{4,0,-1}};

  std::vector<int> c = a.spiralOrder(o);
  for (int &i : c) {
    std::cout << i << ' ';
  }
  return 0;
}

//{1,2,3,4},{5,6,7,8},{9,10,11,12}
//{{2,5,8},{4,0,-1}}
//{{1,2,3},{4,5,6},{7,8,9}}