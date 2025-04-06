#pragma once
#include <vector>
#include <cmath>

class Solution {

 public:
  int maximumDetonation(const std::vector<std::vector<int>> &bombs) {
    int max = Countofdetonation(bombs, 0);
    for (int i = 1; i < bombs.size(); ++i) {
      int k = Countofdetonation(bombs, i);
      if (max < k) {
        max = k;
      }
    }
    return max;
  }

  int Countofdetonation(const std::vector<std::vector<int>> &bombs, int n) {
    int x = bombs[n][0];
    int y = bombs[n][1];
    int r = bombs[n][2];
    std::vector<std::vector<int>> detonated;
    std::vector<std::vector<int>> undetonated;
    for (int i = 0; i < bombs.size(); ++i) {
      if (std::sqrt((long long)(x - bombs[i][0])*(x - bombs[i][0]) + (long long)(y - bombs[i][1])*(y - bombs[i][1])) <= r) {
        detonated.push_back(bombs[i]);
      } else {
        undetonated.push_back(bombs[i]);
      }
    }
    int i = 0;
    while (!undetonated.empty() && i < detonated.size()) {
      for (int j = 0; j < undetonated.size(); ++j) {
        if (std::sqrt((long long)(undetonated[j][0] - detonated[i][0])*(undetonated[j][0] - detonated[i][0]) +
            (long long)(undetonated[j][1] - detonated[i][1])*(undetonated[j][1] - detonated[i][1])) <= detonated[i][2]) {
          detonated.push_back(undetonated[j]);
          undetonated.erase(undetonated.cbegin() + j);
          --j;
        }
      }
      ++i;
    }
    return detonated.size();
  }
};