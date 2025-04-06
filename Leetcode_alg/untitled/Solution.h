#pragma once

int count_of_ways = 0;

class Solution {
 public:
  void try_to_move(std::pair<int, int> &pos, int x, int y) {
    if (pos.first == x && pos.second == y) {
      count_of_ways++;
    } else {
      if (pos.first + 1 <= x) {
        pos.first++;
        try_to_move(pos, x, y);
        pos.first--;
      }
      if (pos.second + 1 <= y) {
        pos.second++;
        try_to_move(pos, x, y);
        pos.second--;
      }
    }
  }

  int uniquePaths(int m, int n) {
    std::pair<int, int> start_pos{0, 0};
    try_to_move(start_pos, n - 1, m - 1);
    return count_of_ways;
  }
};