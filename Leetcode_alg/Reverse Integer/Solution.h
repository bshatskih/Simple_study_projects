#pragma once

class Solution {
 public:
  int reverse(int x) {
    int res = 0;
    while (x != 0) {
      if (res > INT32_MAX/10 || res < INT32_MIN/10) {
        return 0;
      }
      res = res * 10 + x % 10;
      x /= 10;
      std::cout << res << '\n';
    }
    return res;
  }
};

