#ifndef MAXIMUM_PROFIT_IN_JOB_SCHEDULING__SILUTION_H_
#define MAXIMUM_PROFIT_IN_JOB_SCHEDULING__SILUTION_H_


void recursion(std::vector<int>& startTime, std::vector<int>& endTime, std::vector<int>& profit) {
  static size_t max_profit = 0;
  static size_t curr_profit = 0;

  uint32_t length = startTime.size();
  for (uint32_t i : std::ranges::views::iota(static_cast<uint32_t>(0), length - 1)) {
    curr_profit += profit[i];

  }
}


class Solution {
 public:
  int jobScheduling(std::vector<int>& startTime, std::vector<int>& endTime, std::vector<int>& profit) {

  }
};




#endif //MAXIMUM_PROFIT_IN_JOB_SCHEDULING__SILUTION_H_
