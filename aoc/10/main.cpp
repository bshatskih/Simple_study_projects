///part 1
/*#include <iostream>
#include <fstream>

int string_to_number(std::string &str) {
  int number = 0;
  bool flag;
  flag = str[5] == '-';
  for (int i = 5 + flag; i < str.size(); i++) {
    number = number * 10 + (str[i] - '0');
  }
  return flag ? number * -1 : number;
}

int main() {
  std::ifstream fin("../test");
  std::string str;
  if (!fin.is_open()) {
    std::cout << "error";
  }

  size_t strength = 0;
  int X = 1;
  size_t counter = 0;
  int number;
  int prev_number = 0;
  size_t flag = 20;

  while (std::getline(fin, str)) {
    counter++;
    X += prev_number;
    prev_number = 0;
    if (str[0] == 'a') {
      number = string_to_number(str);
      counter++;
      prev_number = number;
    }
    if (counter >= flag) {
      strength += X * flag;
      flag += 40;
    }
  }
  std::cout << strength;
  return 0;
}*/

///part 2

/*
#include <iostream>
#include <fstream>

int string_to_number(std::string &str) {
  int number = 0;
  bool flag;
  flag = str[5] == '-';
  for (int i = 5 + flag; i < str.size(); i++) {
    number = number * 10 + (str[i] - '0');
  }
  return flag ? number * -1 : number;
}

void print(int& curr_pos, int X) {
  if (curr_pos <= X + 1 && curr_pos >= X - 1) {
    std::cout << '#';
  } else {
    std::cout << '.';
  }
  if (curr_pos == 39) {
    curr_pos = 0;
    std::cout << '\n';
  } else {
    curr_pos++;
  }
}

int main() {
  std::ifstream fin("../test");
  std::string str;
  if (!fin.is_open()) {
    std::cout << "error";
  }

  int X = 1;
  int curr_pos = 0;
  size_t size = 0;
  int number;

  while (size < 240) {
      std::getline(fin, str);
      if (str[0] == 'a') {
        number = string_to_number(str);
        print(curr_pos, X);
        print(curr_pos, X);
        X += number;
        size += 2;
      } else {
        print(curr_pos, X);
        size++;
      }
  }
  return 0;
}*/
