#ifndef DETERMINE_IF_STRING_HALVES_ARE_ALIKE__SOLUTION_H_
#define DETERMINE_IF_STRING_HALVES_ARE_ALIKE__SOLUTION_H_

class Solution {
 public:
//  bool halvesAreAlike(std::string s) {
//    short res = 0;
//    std::string vowels{'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
//    for (short i = 0; i < s.length()/2; ++i) {
//      if (vowels.find(s[i]) != std::string::npos) {
//        ++res;
//      }
//    }
//    for (short i = s.length()/2; i < s.length(); ++i) {
//      if (vowels.find(s[i]) != std::string::npos) {
//        --res;
//      }
//    }
//    return !static_cast<bool>(res);
//  }
  bool halvesAreAlike(std::string s) {
    short res = 0;
    std::string vowels{'a', 'e', 'i', 'o', 'u'};
    std::transform(s.begin(), s.end(), s.begin(),::tolower);
    for (short i = 0; i < s.length()/2; ++i) {
      if (vowels.find(s[i]) != std::string::npos) {
        ++res;
      }
    }
    for (short i = s.length()/2; i < s.length(); ++i) {
      if (vowels.find(s[i]) != std::string::npos) {
        --res;
      }
    }
    return !static_cast<bool>(res);
  }
};






#endif //DETERMINE_IF_STRING_HALVES_ARE_ALIKE__SOLUTION_H_
