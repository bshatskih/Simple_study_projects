#include <iostream>
#include <fstream>

unsigned int string_cut(std::string &str, size_t pos1, size_t pos2) {
  std::string answer;
  answer.append(str, pos1, pos2 - pos1);
  return atoi(answer.c_str());
}


int main() {
  std::ifstream fin("../test");
  std::string str;
  int score = 0;
  if (!fin.is_open()) {
    std::cout << "error";
  }
  size_t pos1;
  size_t pos2;
  size_t pos3;
  unsigned int ch1;
  unsigned int ch2;
  unsigned int ch3;
  unsigned int ch4;

  while (std::getline(fin, str)) {
    pos1 = str.find('-');
    pos2 = str.find(',', pos1);
    pos3 = str.find('-', pos2);
    ch1 = string_cut(str, 0, pos1);
    ch2 = string_cut(str, pos1 + 1, pos2);
    ch3 = string_cut(str, pos2 + 1, pos3);
    ch4 = string_cut(str, pos3 + 1, str.size());
    if (!(ch2 < ch3 || ch1 > ch4)) {
      score++;
    }
  }
  std::cout << score;
  return 0;
}
