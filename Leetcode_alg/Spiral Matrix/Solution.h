#pragma once


class Solution {
 public:
  std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
    std::vector<int> res;
    res.reserve(matrix.size() * matrix[0].size());
    int length_j = matrix[0].size();
    int length_i = matrix.size();
    int k = 0;
    while (res.size() != length_i * length_j) {

      for (int j = k; j < length_j - k; ++j) {
        res.push_back(matrix[k][j]);
      }
      bool flag = false;
      for (int i = k + 1; i < length_i - k; ++i) {
        res.push_back(matrix[i][length_j - 1 - k]);
        flag = true;
      }
      bool flag_2 = false;
      if (flag) {
        for (int j = length_j - k - 2; j >= k; --j) {
          res.push_back(matrix[length_i - 1 - k][j]);
          flag_2 = true;
        }
      }
      if (flag_2) {
        for (int i = length_i - k - 2; i > k; --i) {
          res.push_back(matrix[i][k]);
        }
      }
      k++;
    }
    return res;
  }
};