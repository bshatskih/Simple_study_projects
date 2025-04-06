#pragma once

class Solution {
 public:
  std::string countAndSay(int n) {
    if (n == 1)
      return "1";
    std::string str = countAndSay(n - 1);
    std::string tmp;
    int i = 0;
    int count = 1;
    while (i < str.length()) {
      if (i < str.length() - 1 && str[i]==str[i+1])
        count++;
      else
      {
        tmp.push_back(count + '0');
        tmp += str[i];
        count = 1;
      }
      i++;
    }
    return tmp;
  }
};