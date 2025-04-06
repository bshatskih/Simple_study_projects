#pragma once

class Solution {
 public:

  std::string convert(std::string s, int numRows) {
    std::vector<std::string> zigzag(numRows);
    int length = s.size();
    int index = 0;
    int numColumn = 0;
    for (int i = 0; i < length; i += numRows) {
      numColumn++;
      if (numRows > 2) {
        i += numRows - 2;
      }
    }
    int i = 0;
    while (i < numColumn) {
      int j = 0;
      while (index < length && j < numRows) {
        zigzag[j].push_back(s[index]);
        index++;
        j++;
      }
      j = numRows - 2;
      while (index < length && j > 0) {
        zigzag[j].push_back(s[index]);
        index++;
        j--;
      }
      i++;
    }
    std::string res;
    res.reserve(length);
    for (i = 0; i < numRows; i++) {
      res += zigzag[i];
    }
    return res;
  }
};