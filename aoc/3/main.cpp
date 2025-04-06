#include <iostream>
#include <fstream>

int main() {
  std::ifstream fin("../test");
  std::string str_1;
  std::string str_2;
  std::string str_3;
  int score = 0;
  if (!fin.is_open()) {
    std::cout << "error";
  }
  bool flag;
  while (std::getline(fin, str_1)) {
    std::getline(fin, str_2);
    std::getline(fin, str_3);
    flag = true;
    for (size_t i = 0; i < str_1.length() && flag; i++) {
      if (str_2.find(str_1[i]) != std::string::npos && str_3.find(str_1[i]) != std::string::npos) {
        flag = false;
        if (static_cast<int>(str_1[i]) >= 97) {
          score += str_1[i] - 'a' + 1;
        } else {
          score += str_1[i] - 'A' + 27;
        }
      }
    }
  }
  std::cout << score;
  return 0;
}
