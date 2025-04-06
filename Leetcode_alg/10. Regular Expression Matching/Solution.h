#ifndef INC_10__REGULAR_EXPRESSION_MATCHING__10_REGULAR_EXPRESSION_MATCHING_SOLUTION_H_
#define INC_10__REGULAR_EXPRESSION_MATCHING__10_REGULAR_EXPRESSION_MATCHING_SOLUTION_H_

class Solution {
 public:
  bool isMatch(std::string &s, std::string &p) {

    bool result{true};
    char prev_ch;
    bool is_prev_ch_normal = !(p[0] == '*' || p[0] == '.');
    if (!is_prev_ch_normal) {
      if (p[0] == '*')
        result = false;
      else
        prev_ch = s[0];
    }
    for (int i = 0; i < s.length() && result; ++i) {
      switch (p[i]) {
        case '.': {
          prev_ch = s[i];
          break;
        }
        case '*': {
          if (!is_prev_ch_normal) {
            if (s[i] >= prev_ch)
              prev_ch = s[i];
          }
        }

      }
    }
  }
};

#endif //INC_10__REGULAR_EXPRESSION_MATCHING__10_REGULAR_EXPRESSION_MATCHING_SOLUTION_H_
