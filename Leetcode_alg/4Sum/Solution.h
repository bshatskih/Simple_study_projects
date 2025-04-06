#pragma once


class Solution {
 public:

  std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
    int length = nums.size();
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> res;
    int start = 0;
    while (start < length - 3) {
      while (start > 0 && start < length - 3 && nums[start] == nums[start - 1]) {
        start++;
      }
      int i = start + 1;
      while (i < length - 2) {
        while (i > start + 1 && i < length - 2 && nums[i] == nums[i - 1]) {
          i++;
        }
        int k = length - 1;
        int j = i + 1;
        while (j < k) {
          long long sum = (long long)nums[start] + (long long)nums[j] + (long long)nums[k] + (long long)nums[i];
          if (sum == target) {
            res.push_back({nums[start], nums[j], nums[k], nums[i]});
            k--;
            while (k > j && nums[k] == nums[k + 1]) {
              k--;
            }
            j++;
            while (j > start + 1 && j < length && nums[j] == nums[j - 1]) {
              j++;
            }
          } else if (sum > target) {
            k--;
            while (k > j && nums[k] == nums[k + 1]) {
              k--;
            }
          } else {
            j++;
            while (j > start + 1 && j < length && nums[j] == nums[j - 1]) {
              j++;
            }
          }
        }
        i++;
      }
      start++;
    }
    return res;
  }
};