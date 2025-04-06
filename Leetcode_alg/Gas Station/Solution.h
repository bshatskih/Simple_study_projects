#pragma once

class Solution {
 public:
  int canCompleteCircuit(std::vector<int> &gas, std::vector<int> &cost) {
    int length = gas.size();
    std::vector<int> difference(length);
    long long sum = 0;
    for (int i = 0; i < length; ++i) {
      gas[i] -= cost[i];
      sum += gas[i];
    }
    if (sum < 0) {
      return -1;
    }
    if (length == 1 && gas[0] >= 0) {
      return 0;
    }
    int max = gas[0];
    int index_max = 0;
    for (int i = 0; i < length; i++) {
      if (gas[i] > max) {
        max = gas[i];
        index_max = i;
      }
    }
    int j = (index_max + 1) % length;
    int fuel = gas[index_max];
    while (j != index_max && fuel >= 0) {
      fuel += gas[j];
      j = (j + 1) % length;
    }
    if (fuel >= 0) {
      return index_max;
    }
    for (int i = 0; i < length; ++i) {
      if (gas[i] > 0) {
        int j = (i + 1) % length;
        int fuel = gas[i];
        while (j != i && fuel >= 0) {
          fuel += gas[j];
          j = (j + 1) % length;
        }
        if (fuel >= 0) {
          return i;
        }
      }
    }
    return -1;
  }
};