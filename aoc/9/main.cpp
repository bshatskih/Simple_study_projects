
///part 1
/*#include <iostream>
#include <fstream>
#include <set>

int string_to_number(std::string &str) {
  int number = 0;
  for (int i = 2; i < str.size(); i++) {
    number = number * 10 + (str[i] - '0');
  }
  return number;
}

int distance(const std::pair<int, int> &T, const std::pair<int, int> &H) {
  return (T.first - H.first)*(T.first - H.first) + (T.second - H.second)*(T.second - H.second);
}

int main() {
  std::ifstream fin("../test");
  std::string str;
  if (!fin.is_open()) {
    std::cout << "error";
  }
  std::set<std::pair<int, int>> way;
  way.insert({0, 0});

  std::pair<int, int> coordinates_head{0, 0};
  std::pair<int, int> coordinates_tail{0, 0};


  int length;
  while (std::getline(fin, str)) {
    length = string_to_number(str);
    switch (str[0]) {
      case 'U':
        for (int i = 0; i < length; i++) {
          coordinates_head.second++;
          if (distance(coordinates_tail, coordinates_head) == 4) {
            coordinates_tail.second++;
            way.insert(coordinates_tail);
          } else if (distance(coordinates_tail, coordinates_head) == 5) {
            if (coordinates_head.first > coordinates_tail.first) {
              coordinates_tail.first++;
            } else {
              coordinates_tail.first--;
            }
            coordinates_tail.second++;
            way.insert(coordinates_tail);
          }
        }
        break;

      case 'D':
        for (int i = 0; i < length; i++) {
          coordinates_head.second--;
          if (distance(coordinates_tail, coordinates_head) == 4) {
            coordinates_tail.second--;
            way.insert(coordinates_tail);
          } else if (distance(coordinates_tail, coordinates_head) == 5) {
            if (coordinates_head.first > coordinates_tail.first) {
              coordinates_tail.first++;
            } else {
              coordinates_tail.first--;
            }
            coordinates_tail.second--;
            way.insert(coordinates_tail);
          }
        }
        break;

      case 'L':
        for (int i = 0; i < length; i++) {
          coordinates_head.first--;
          if (distance(coordinates_tail, coordinates_head) == 4) {
            coordinates_tail.first--;
            way.insert(coordinates_tail);
          } else if (distance(coordinates_tail, coordinates_head) == 5) {
            if (coordinates_head.second > coordinates_tail.second) {
              coordinates_tail.second++;
            } else {
              coordinates_tail.second--;
            }
            coordinates_tail.first--;
            way.insert(coordinates_tail);
          }
        }
        break;

      case 'R':
        for (int i = 0; i < length; i++) {
          coordinates_head.first++;
          if (distance(coordinates_tail, coordinates_head) == 4) {
            coordinates_tail.first++;
            way.insert(coordinates_tail);
          } else if (distance(coordinates_tail, coordinates_head) == 5) {
            if (coordinates_head.second > coordinates_tail.second) {
              coordinates_tail.second++;
            } else {
              coordinates_tail.second--;
            }
            coordinates_tail.first++;
            way.insert(coordinates_tail);
          }
        }
        break;
      default:
        std::cout << "error";
        break;
    }
  }
  std::cout << way.size();
  return 0;
}*/

///part 2

/*
#include <iostream>
#include <fstream>
#include <set>

int string_to_number(std::string &str) {
  int number = 0;
  for (int i = 2; i < str.size(); i++) {
    number = number * 10 + (str[i] - '0');
  }
  return number;
}

int distance(const std::pair<int, int> &T, const std::pair<int, int> &H) {
  return (T.first - H.first) * (T.first - H.first) + (T.second - H.second) * (T.second - H.second);
}

bool move(std::pair<int, int> &T, const std::pair<int, int> &H) {
  bool flag = true;
  if (distance(T, H) == 4) {
    if (H.first - T.first == 2)
      T.first++;
    else if (H.first - T.first == -2)
      T.first--;
    else if (H.second - T.second == 2)
      T.second++;
    else if (H.second - T.second == -2)
      T.second--;
  } else if (distance(T, H) >= 5) {
    if (H.first > T.first) {
      T.first++;
    } else {
      T.first--;
    }
    if (H.second - T.second > 0)
      T.second++;
    if (H.second - T.second < 0)
      T.second--;
  } else {
    flag = false;
  }
  return flag;
}

int main() {
  std::ifstream fin("../test");
  std::string str;
  if (!fin.is_open()) {
    std::cout << "error";
  }
  std::set<std::pair<int, int>> way;
  way.insert({0, 0});

  auto *nodes = new std::pair<int, int>[10];
  for (int i = 0; i < 10; i++) {
    nodes[i].first = nodes[i].second = 0;
  }

  int pos;
  int length;
  bool flag;
  while (std::getline(fin, str)) {
    length = string_to_number(str);
    pos = 0;
    switch (str[0]) {
      case 'U':
        for (int i = 0; i < length; i++) {
          nodes[pos].second++;
          flag = true;
          while (pos < 9 && flag) {
            flag = move(nodes[pos + 1], nodes[pos]);
            if (pos == 8 && flag) {
              way.insert(nodes[pos + 1]);
            }
            pos++;
          }
          pos = 0;
        }
        break;

      case 'D':
        for (int i = 0; i < length; i++) {
          nodes[pos].second--;
          flag = true;
          while (pos < 9 && flag) {
            flag = move(nodes[pos + 1], nodes[pos]);
            if (pos == 8 && flag) {
              way.insert(nodes[pos + 1]);
            }
            pos++;
          }
          pos = 0;
        }
        break;

      case 'L':
        for (int i = 0; i < length; i++) {
          nodes[pos].first--;
          flag = true;
          while (pos < 9 && flag) {
            flag = move(nodes[pos + 1], nodes[pos]);
            if (pos == 8 && flag) {
              way.insert(nodes[pos + 1]);
            }
            pos++;
          }
          pos = 0;
        }
        break;

      case 'R':
        for (int i = 0; i < length; i++) {
          nodes[pos].first++;
          flag = true;
          while (pos < 9 && flag) {
            flag = move(nodes[pos + 1], nodes[pos]);
            if (pos == 8 && flag) {
              way.insert(nodes[pos + 1]);
            }
            pos++;
          }
          pos = 0;
        }
        break;

      default:std::cout << "error";
        break;
    }
  }
  std::cout << way.size();
  delete[] nodes;
  return 0;
}*/
