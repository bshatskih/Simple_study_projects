#pragma once

class Solution {
 public:
  int maximumTop(std::vector<int>& nums, int k) {
    int length = nums.size();
    if (k % 2 == 0 && length == 1) {
      return -1;
    }
    if (k == 1 && length >= 2) {
      return nums[k];
    }
    int max = nums[0];
    for (int i = 1; i < std::min(k - 1, length); ++i) {
      if (max < nums[i]) {
        max = nums[i];
      }
    }
    if (max < nums[k]) {
      max = nums[k];
    }
    return max;
  }
};