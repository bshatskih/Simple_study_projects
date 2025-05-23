#pragma once

class Solution {
 public:

  double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    if(nums1.empty() || nums2.empty()) {
      if(nums1.size() == 1 || nums2.size() == 1)
        return nums1.empty() ? nums2.back() : nums1.back();
      else {
        int n = std::max(nums1.size(), nums2.size());
        std::vector<int>& nonEmpty = nums1.empty() ? nums2 : nums1;
        int index = n /2;
        if(n % 2 == 1) {
          return nonEmpty[index];
        }
        else {
          return (static_cast<double>(nonEmpty[index]) + nonEmpty[index-1]) / 2;
        }
      }
    }
    if(nums1.size() == 1 && nums2.size() == 1) {
      return (static_cast<double>(nums1[0]) + nums2[0]) / 2;
    }

    int left1 = 0;
    int left2 = 0;
    int n1 = nums1.size();
    int n2 = nums2.size();

    int n = n1 + n2;
    int index = n / 2;
    int lastChanged = 0;

    while (left1 + left2 != index) {
      if((left2 == n2 || left1 < n1 && nums1[left1] < nums2[left2]) ) {
        lastChanged = 1;
        ++left1;
      }
      else {
        lastChanged = 2;
        ++left2;
      }
    }

    if(n % 2 == 1) {
      int result = 10000000;
      if(left1 < n1) {
        result = std::min(result, nums1[left1]);
      }
      if(left2 < n2) {
        result = std::min(result, nums2[left2]);
      }
      return result;
    }
    else {
      double first = 0;
      if(lastChanged == 1) {
        first = nums1[left1-1];
        int nextValueInFirst = 1000000;
        int nextValueInSecond = 1000000;
        if(left1 < n1) {
          while(left1 < n1 && nums1[left1] < first) {
            ++left1;
          }
          if(left1 < n1) {
            nextValueInFirst = nums1[left1];
          }
        }
        if(left2  < n2) {
          while(left2 < n2 && nums2[left2] < first) {
            ++left2;
          }
          if(left2 < n2) {
            nextValueInSecond = nums2[left2];
          }
        }
        return (first + std::min(nextValueInSecond, nextValueInFirst)) / 2;
      }
      else {
        first = nums2[left2-1];
        int nextValueInFirst = 1000000;
        int nextValueInSecond = 1000000;
        if(left2 < n2) {
          while(left2 < n2 && nums2[left2] < first) {
            ++left2;
          }
          if(left2 < n2) {
            nextValueInFirst = nums2[left2];
          }
        }
        if(left1 < n1) {
          while(left1 < n1 && nums1[left1] < first) {
            ++left1;
          }
          if(left1 < n1) {
            nextValueInSecond = nums1[left1];
          }
        }
        return (first + std::min(nextValueInSecond, nextValueInFirst)) / 2;
      }
    }
  }
};


