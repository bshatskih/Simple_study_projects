#pragma once


class Solution {
 public:

  void new_iteration(std::vector<int>& num, std::map<int, int>& memory, int sum, int& answer) {
    if (sum == 0) {
      answer++;
      return;
    }

    for (int i = 0; i < num.size(); i++) {
      if (sum - num[i] >= 0) {
        if (memory.contains(sum - num[i])) {
          answer += memory[sum - num[i]];
        } else {
          int copy_answer = answer;
          new_iteration(num, memory, sum - num[i], answer);
          memory[sum - num[i]] = answer - copy_answer;
        }
      } else {
        break;
      }
    }
  }

  int combinationSum4(std::vector<int>& nums, int target) {
    std::sort(nums.begin(), nums.end());
    int answer = 0;
    std::map<int, int> memory;
    new_iteration(nums, memory, target, answer);
    return answer;
  }
};

