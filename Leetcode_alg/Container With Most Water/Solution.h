#ifndef CONTAINER_WITH_MOST_WATER__SOLUTION_H_
#define CONTAINER_WITH_MOST_WATER__SOLUTION_H_



class Solution {
 public:

  int maxArea(std::vector<int>& height) {
//    int max_volume{0};
//    int cur_volume;
//    bool flag = true;
//    for (int32_t i = 0; i < height.size(); ++i) {
//      for (int32_t j = height.size() - 1; j > i && flag; --j) {
//        cur_volume = std::min(height[i], height[j]) * (j - i);
//        if (cur_volume > max_volume) {
//          max_volume = cur_volume;
//        }
//        if (height[j] >= height[i]) {
//          flag = false;
//        }
//      }
//      flag = true;
//    }
    int left = 0;
    int right = height.size() - 1;
    int max_volume = 0;

    while (left < right) {
      max_volume = std::max(max_volume, std::min(height[left], height[right]) * (right - left));
      if (height[left] < height[right]) {
        left++;
      } else {
        right--;
      }
    }
    return max_volume;
  }

};




#endif //CONTAINER_WITH_MOST_WATER__SOLUTION_H_
