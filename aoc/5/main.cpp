#include <iostream>
#include <fstream>
#include <vector>

unsigned int string_cut(std::string &str, size_t pos) {
  std::string answer;
  size_t i = pos;
  while (isdigit(str[i])) {
    answer += str[i];
    i++;
  }
  return atoi(answer.c_str());
}

void reverse_insertion(std::string& str1, std::string& str2, size_t count) {
  std::string s;
  for (int i = count - 1; i >= 0; i--) {
    s += str2[i];
  }
  str1.insert(0, s);
}


int main() {
  std::ifstream fin("../test");
  std::string str;
  std::vector<std::string> data;
  if (!fin.is_open()) {
    std::cout << "error";
  }
  while (std::getline(fin, str) && !str.empty()) {
    data.push_back(str);
  }
  size_t pos = 1;
  size_t size = data[data.size() - 1][data[data.size() - 1].size() - 1] - '0';
  std::vector<std::string> sort_data(size);
  data.pop_back();
  for (std::string &i : sort_data) {
    for (std::string &s : data) {
      if (pos < s.size() && s[pos] != ' ') {
        i += s[pos];
      }
    }
    pos += 4;
  }

  size_t pos1;
  size_t pos2;
  size_t pos3;
  unsigned int count;
  unsigned int from;
  unsigned int to;

  while (std::getline(fin, str)) {
    pos1 = str.find(' ') + 1;
    pos2 = str.find(' ', str.find(' ', pos1) + 1) + 1;
    pos3 = str.rfind(' ') + 1;
    count = string_cut(str, pos1);
    from = string_cut(str, pos2) - 1;
    to = string_cut(str, pos3) - 1;
//    reverse_insertion(sort_data[to], sort_data[from], count);
    sort_data[to].insert(0, sort_data[from], 0, count);
    sort_data[from].erase(0, count);
  }
  for (std::string &s : sort_data) {
    std::cout << s[0];
  }
  return 0;
}
