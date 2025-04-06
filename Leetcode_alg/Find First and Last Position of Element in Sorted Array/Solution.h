#pragma once


class Solution {
 public:

  int Binary_Search(std::vector<int> *a, int key) {
    int start = -1;
    int end = (*a).size();
    while (end - start >= 2) {
      if ((*a)[(end + start) / 2] < key) {
        start = (end + start) / 2;
      } else if ((*a)[(end + start) / 2] > key) {
        end = (end + start) / 2;
      } else {
        return (end + start) / 2;
      }
    }
    return -1;
  }

  std::vector<int> searchRange(std::vector<int>& nums, int target) {
    int pos = Binary_Search(&nums, target);
    int length = nums.size();
    std::vector<int> res(2);
    if (pos == -1) {
      res[0] = -1;
      res[1] = -1;
      return res;
    }
    int i = pos;
    while (i < length && nums[i] == nums[pos]) {
      i--;
    }
    i++;
    res[0] = i;
    i = pos;
    while (i < length && nums[i] == nums[pos]) {
      i++;
    }
    i--;
    res[1] = i;
    return res;
  }
};