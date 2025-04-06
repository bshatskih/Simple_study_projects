#pragma once

class Solution {
 public:
  int myAtoi(std::string s) {
    int index = 0;
    bool sign = true;
    while (s[index] == ' ') {
      index++;
    }
    if (s[index] == '-') {
      sign = false;
      index++;
    } else if (s[index] == '+') {
      index++;
    }
    int ch = 0;
    if (!std::isdigit(s[index])) {
      return ch;
    }
    int end = index;
    bool flag = true;
    while (std::isdigit(s[end])) {
      end++;
      if (s[index] != '0') {
        flag = false;
      }
      if (flag && s[end] == '0') {
        index++;
      }
    }
    int k = 1;
    for (int i = --end; i >= index; i--) {
      if (ch > INT32_MAX % 1000000000 && s[i] - '0' > 1 || k > INT32_MAX) {
        if (sign) {
          ch = INT32_MAX;
        } else {
          ch = INT32_MIN;
        }
        break;
      }
      ch += (s[i] - '0') * k;
      k *= 10;
    }
    if (!sign && ch != INT32_MIN) {
      ch *= -1;
    }
    return ch;
  }
};