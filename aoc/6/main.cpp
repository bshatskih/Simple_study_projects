#include <iostream>
#include <fstream>

bool search_marker(std::string& str, unsigned int start_pos) {
  bool flag;
  for (unsigned int i = start_pos; i < start_pos + 13; i++) {
    for (unsigned int j = i + 1; j < start_pos + 14; j++) {
      if (str[i] == str[j]) {
        return true;
      }
    }
  }
  return false;
}


int main() {
  std::ifstream fin("../test");
  std::string str;
  if (!fin.is_open()) {
    std::cout << "error";
  }
  std::getline(fin, str);
  bool flag = true;
  int i = 0;

  while (flag && i < str.length()) {
    flag = search_marker(str, i);
    i++;
  }
  std::cout << i + 13;
  return 0;
}
