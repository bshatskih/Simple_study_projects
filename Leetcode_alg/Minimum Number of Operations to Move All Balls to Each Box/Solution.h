#pragma once

class Solution {
 public:
  std::vector<int> minOperations(std::string boxes) {
    std::vector<int> result;
    for (int i = 0; i < boxes.size(); ++i) {
      int difference=0;
      for (int j = 0; j < boxes.size(); ++j) {
        if (boxes[j] == '1' && j != i)
          difference += abs(i - j);
      }
      result.push_back(difference);
    }
    return result;
  }
};


//  if (boxes[j] == '1' && j != i)
//  result[i] += abs(i - j);