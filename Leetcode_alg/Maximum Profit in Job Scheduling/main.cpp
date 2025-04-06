#include <iostream>
#include <vector>
#include <cstdint>
#include <ranges>
#include "Silution.h"

int main() {
  Solution a;
  std::vector<int> startTime{1,2,3,3};
  std::vector<int> endTime{3,4,5,6};
  std::vector<int> profit{50,10,40,70};

  a.jobScheduling(startTime, endTime, profit);
//  std::cout <<  << std::endl;
  return 0;
}
