#pragma once

class Hill_Climbing {
  std::vector<std::string> map;
  std::vector<std::vector<short>> tag;

 public:

  short& get_tag(int i, int j) {
    return tag[i][j];
  }

  explicit Hill_Climbing(std::ifstream &fin) {
    fin.open("../test");
    if (!fin.is_open()) {
      std::cout << "error";
    }
    std::string str;
    while (std::getline(fin, str)) {
      map.push_back(str);
    }
    std::vector<short> a(map[0].size());

    for (short &i : a)
      i = 0;

    for (int i = 0; i < map.size(); i++) {
      tag.push_back(a);
    }
  }

  std::pair<int, int> find_start_pos() {
    for (size_t i = 0; i < map.size(); i++) {
      if (map[i].find('S') != std::string::npos) {
        size_t pos = map[i].find('S');
        map[i][pos] = 'a';
        return {i, pos};
      }
    }
  }

  std::pair<int, int> find_end_pos() {
    for (size_t i = 0; i < map.size(); i++) {
      if (map[i].find('E') != std::string::npos) {
        size_t pos = map[i].find('E');
        map[i][pos] = 'z';
        return {i, pos};
      }
    }
  }

  int geolocation(std::pair<int, int> pos) {
    if (pos.first == 0) {
      if (pos.second == 0) {
        return 1;
      } else if (pos.second == map[0].length() - 1) {
        return 3;
      } else {
        return 2;
      }
    } else if (pos.first == map.size() - 1) {
      if (pos.second == 0) {
        return 7;
      } else if (pos.second == map[0].length() - 1) {
        return 5;
      } else {
        return 6;
      }
    } else {
      if (pos.second == 0) {
        return 8;
      } else if (pos.second == map[0].length() - 1) {
        return 4;
      } else {
        return 9;
      }
    }
  }

  bool move_left(std::pair<int, int> &prev_start_pos, std::pair<int, int> &start_pos) {
    if (abs(map[start_pos.first][start_pos.second - 1] - map[start_pos.first][start_pos.second]) <= 1 &&
        prev_start_pos.second != start_pos.second - 1  && tag[start_pos.first][start_pos.second - 1] == 0) {
      prev_start_pos = start_pos;
      start_pos.second--;
      tag[start_pos.first][start_pos.second] = 1;
      return true;
    }
    return false;
  }

  bool move_right(std::pair<int, int> &prev_start_pos, std::pair<int, int> &start_pos) {
    if (abs(map[start_pos.first][start_pos.second + 1] - map[start_pos.first][start_pos.second]) <= 1 &&
        prev_start_pos.second != start_pos.second + 1 && tag[start_pos.first][start_pos.second + 1] == 0) {
      prev_start_pos = start_pos;
      start_pos.second++;
      tag[start_pos.first][start_pos.second] = 1;
      return true;
    }
    return false;
  }

  bool move_up(std::pair<int, int> &prev_start_pos, std::pair<int, int> &start_pos) {
    if (abs(map[start_pos.first - 1][start_pos.second] - map[start_pos.first][start_pos.second]) <= 1 &&
        prev_start_pos.first != start_pos.first - 1 && tag[start_pos.first - 1][start_pos.second] == 0) {
      prev_start_pos = start_pos;
      start_pos.first--;
      tag[start_pos.first][start_pos.second] = 1;
      return true;
    }
    return false;
  }

  bool move_down(std::pair<int, int> &prev_start_pos, std::pair<int, int> &start_pos) {
    if (abs(map[start_pos.first + 1][start_pos.second] - map[start_pos.first][start_pos.second]) <= 1 &&
        prev_start_pos.first != start_pos.first + 1 && tag[start_pos.first + 1][start_pos.second] == 0) {
      prev_start_pos = start_pos;
      start_pos.first++;
      tag[start_pos.first][start_pos.second] = 1;
      return true;
    }
    return false;
  }

  void move_back(std::pair<int, int> &start_pos,
                 std::pair<int, int> &prev_start_pos,
                 size_t &count,
                 std::pair<int, int> copy_prev) {
    tag[start_pos.first][start_pos.second] = 0;
    count--;
    start_pos = prev_start_pos;
    prev_start_pos = copy_prev;
  }

  void find_way(std::pair<int, int> prev_start_pos,
                std::pair<int, int> start_pos,
                std::pair<int, int> &end_pos,
                std::vector<size_t> &answer) {
    static size_t count = 0;

    int pos_flag = geolocation(start_pos);

    if (start_pos == end_pos) {
      answer.push_back(count);
      return;
    }

    std::pair<int, int> copy_prev = prev_start_pos;

    switch (pos_flag) {
      case 1:
        if (move_right(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        if (move_down(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        return;
        break;
      case 2:
        if (move_left(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        if (move_right(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        if (move_down(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        return;
        break;
      case 3:
        if (move_left(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        if (move_down(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        return;
        break;
      case 4:
        if (move_left(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        if (move_down(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        if (move_up(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        return;
        break;
      case 5:
        if (move_left(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        if (move_up(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        return;
        break;
      case 6:
        if (move_right(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        if (move_left(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        if (move_up(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        return;
        break;
      case 7:
        if (move_right(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        if (move_up(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        return;
        break;
      case 8:
        if (move_down(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        if (move_right(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        if (move_up(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        return;
        break;
      case 9:
        if (move_down(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        if (move_up(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        if (move_right(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        if (move_left(prev_start_pos, start_pos)) {
          count++;
          find_way(prev_start_pos, start_pos, end_pos, answer);
          move_back(start_pos, prev_start_pos, count, copy_prev);
        }
        return;
        break;
      default:std::cout << "bad format";
        break;
    }
  }

};