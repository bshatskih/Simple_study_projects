#pragma once

class Optimal_Solution {
 public:
  int canCompleteCircuit(std::vector<int> &gas, std::vector<int> &cost) {
    int a = 0, b = 0;
    for (int i = 0; i < gas.size(); i++) {
      a += gas[i];
      b += cost[i];
    }

    if (a < b) return -1;

    int cT = 0;
    int canBe = -1;
    for (int i = 0; i < gas.size(); i++) {
      cT += gas[i] - cost[i];
      if (cT >= 0 && canBe == -1) {
        canBe = i;
      }
      else if (cT < 0) {
        cT = 0;
        canBe = -1;
      }
    }
    return canBe;
  }
};