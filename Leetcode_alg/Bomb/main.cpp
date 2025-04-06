#include <iostream>
#include "Solution.h"
#include "Optimal_Solution.h"

int main() {
  std::vector<std::vector<int>> g = {{1,2,3},{2,3,1},{3,4,2},{4,5,3},{5,6,4}};
  Optimal_Solution a;
  std::cout << a.maximumDetonation(g);
  return 0;
}


//{{1,2,3},{2,3,1},{3,4,2},{4,5,3},{5,6,4}}