#include <iostream>
#include <fstream>
#include <vector>

int main() {
  std::ifstream fin("../test");
  std::string str;
  if (!fin.is_open()) {
    std::cout << "error";
  }
  std::vector<std::string> grid;
  while (std::getline(fin, str)) {
    grid.push_back(str);
  }
  size_t score = 1;
  size_t max_score = 1;
//  std::cout << count << '\n';
  for (size_t i = 1; i < grid.size() - 1; i++) {
    for (size_t j = 1; j < str.length() - 1; j++) {
      bool flag = true;
      size_t ch = 0;
      for (size_t k = i + 1; k < grid.size() && flag; k++) {
        if (grid[i][j] <= grid[k][j]) {
          flag = false;
        }
        ch++;
      }
      score *= ch;
      flag = true;
      ch = 0;
      for (int k = i - 1; k >= 0 && flag; k--) {
        if (grid[i][j] <= grid[k][j]) {
          flag = false;
        }
        ch++;
      }
      flag = true;
      score *= ch;
      ch = 0;
      for (size_t k = j + 1; k < str.length() && flag; k++) {
        if (grid[i][j] <= grid[i][k]) {
          flag = false;
        }
        ch++;
      }
      flag = true;
      score *= ch;
      ch = 0;
      for (int k = j - 1; k >= 0 && flag; k--) {
        if (grid[i][j] <= grid[i][k]) {
          flag = false;
        }
        ch++;
      }
      score *= ch;
      if (score > max_score) {
        max_score = score;
      }
      score = 1;
    }
  }
  std::cout << max_score;
  return 0;
}
