#ifndef KTH_LARGEST_ELEMENT_IN_AN_ARRAY__SOLUTION_H_
#define KTH_LARGEST_ELEMENT_IN_AN_ARRAY__SOLUTION_H_


class Solution {
 public:
  int findKthLargest(std::vector<int>& nums, int k) {
//    std::map<int, int> res;
//    for (const int& num: nums) {
//      if (res.contains(num)) {
//        res[num]++;
//      } else {
//        res[num] = 1;
//      }
//    }
//
//    std::map<int, int>::const_reverse_iterator cit = res.crbegin();
//    int counter = cit->second;
//    while (counter < k) {
//      ++cit;
//      counter += cit->second;
//    }
//    return cit->first;

//  std::ranges::sort(nums);
  std::sort(std::begin(nums), std::end(nums));
  return nums[nums.size() - k];
  }
};




#endif //KTH_LARGEST_ELEMENT_IN_AN_ARRAY__SOLUTION_H_
