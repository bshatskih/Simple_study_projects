#pragma once
#include <vector>

class Optimal_Solution {
 public:

  int Boom(std::vector<std::vector<int>>& graph, std::vector<int>& tags, int index, int boom_id) {
    tags[index] = boom_id;
    int res = 1;
    for (int i : graph[index]) {
      if (tags[i] == boom_id)
        continue;
      res += Boom(graph, tags, i, boom_id);
    }
    return res;
  };

  int maximumDetonation(std::vector<std::vector<int>>& bombs) {
    int length = bombs.size();
    std::vector<std::vector<int>> graph(length);
    std::vector<int> tags(length,-1);

    //distance between coordinators of bombs
    auto Distance_2 = [](std::vector<int>& left, std::vector<int>& right) {
      long long dx = right[0] - left[0];
      long long dy = right[1] - left[1];
      long double res = (dx * dx) + (dy * dy);
      return res;
    };

    long long r1_2;
    long long r2_2;
    long double d_2;

    for (int i = 0; i < length - 1; i++) {
      r1_2 = bombs[i][2];
      r1_2 *= r1_2;                //R^2 of i-th bomb
      for (int j = i + 1; j < length; j++) {
        d_2 = Distance_2(bombs[i], bombs[j]);
        if (r1_2 >= d_2) {
          graph[i].push_back(j);   //i-th bomb detonate j-th bomb
        }
        r2_2 = bombs[j][2];
        r2_2 *= r2_2;              //R^2 of j-th bomb
        if (r2_2 >= d_2) {
          graph[j].push_back(i);
        }
      }
    }
//    for (const std::vector<int>& i : graph) {
//      for (int j : i) {
//        std::cout << j << ' ';
//      }
//      std::cout << '\n';
//    }

    int max = 1;
    for (int i = 0; i < length; i++) {
      if (tags[i] > -1) continue;
      int count = Boom(graph, tags, i, i);
      if (count > max) {
        max = count;
      }
    }

    return max;
  }
};