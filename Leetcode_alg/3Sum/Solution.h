#pragma once

class Solution {
 public:

  std::vector<std::vector<int>> threeSum(std::vector<int> &nums) {
    int length = nums.size();
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> res;
    for (int i = 0; i < length - 2; i++) {
      while (i > 0 && i < length - 2 && nums[i] == nums[i - 1]) {
        i++;
      }
      int k = length - 1;
      int j = i + 1;
      while (j < k) {
        int sum = nums[i] + nums[j] + nums[k];
        if (sum == 0) {
          res.push_back({nums[i], nums[j], nums[k]});
          k--;
          while (k > j + 1 && nums[k] == nums[k + 1]) {
            k--;
          }
          j++;
          while (j > i + 1 && j < length && nums[j] == nums[j - 1]) {
            j++;
          }
        } else if (sum > 0) {
          k--;
          while (k > j + 1 && nums[k] == nums[k + 1]) {
            k--;
          }
        } else {
          j++;
          while (j > i + 1 && j < length && nums[j] == nums[j - 1]) {
            j++;
          }
        }
      }
    }
    return res;
  }
};