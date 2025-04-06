#include <iostream>
#include <fstream>
#include <vector>
#include "Hill_Climbing.h"


int main() {
  std::ifstream fin;
  Hill_Climbing a(fin);

  std::pair<int, int> S = a.find_start_pos();
  std::pair<int, int> E = a.find_end_pos();
  a.get_tag(S.first, S.second) = 1;



//  std::cout << S.first << ' ' << S.second;

  std::pair<int, int> prev_S = S;
  std::vector<size_t> answer;
  a.find_way(prev_S, S, E, answer);
//  for (int i = 0; i < 5; i++) {
//    for (int j = 0; j < 8; j++) {
//      std::cout << a.geolocation({i, j});
//    }
//    std::cout << '\n';
//  }
//  for (size_t& i: answer) {
//    std::cout << i << ' ';
//  }
//  if (answer.empty()) {
//    std::cout << "loh";
//  }

  size_t min = answer[0];
  for (size_t i: answer) {
    if (i < min) {
      min = i;
    }
  }
  std::cout << min;

  return 0;
}
