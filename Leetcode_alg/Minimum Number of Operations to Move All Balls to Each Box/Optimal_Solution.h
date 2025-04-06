#pragma once

class Optimal_Solution {
 public:
  std::vector<int> minOperations(std::string boxes) {
    int onesCount = 0;
    int onesTotalIndex = 0;
    int lindex = 0;
    int lones = 0;
    std::vector<int> res;
    for (int i = 0; i < boxes.length(); i++) {
      if (boxes[i] == '1') {
        onesCount++;
        onesTotalIndex = onesTotalIndex + i;
      }
    }
    // 1 1 0
    for (int j = 0; j < boxes.length(); j++) {
      if (boxes[j] == '1') {
        onesTotalIndex = onesTotalIndex - j;
        lones++;
        onesCount--;
      }
      int operations = onesTotalIndex - (j * onesCount) + lindex;
      res.push_back(operations);
      lindex = lindex + lones;
    }

    return res;
  }
};