#pragma once

class Solution {
 public:
  int countPoints(std::string &rings) {
    std::vector<std::string> rods(10);
    int length = rings.size();
    int i = 1;
    while (i <= length) {
      rods[rings[i] - '0'].push_back(rings[i - 1]);
      i+=2;
    }
    bool R, G, B;
    int count = 0;
    for (std::string &j : rods) {
      i = 0;
      R = false;
      G = false;
      B = false;
      while (i < j.size() && !(j.empty() || R && G && B)) {
        if (j[i] == 'R') {
          R = true;
        }
        if (j[i] == 'G') {
          G = true;
        }
        if (j[i] == 'B') {
          B = true;
        }
        i++;
      }
      if (R && G && B) {
        count++;
      }
    }
    return count;
  }
};

