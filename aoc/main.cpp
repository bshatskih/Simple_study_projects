#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Key {
  size_t data{};
  bool flag = false;
  bool operator==(const Key &other) const {
    return data == other.data && flag == other.flag;
  }
  };

  void print_cards(std::vector<std::vector<Key>> &players) {
    for (std::vector<Key> &i : players) {
      for (Key &j : i) {
        std::cout << '{' << j.data << ", " << j.flag << '}' << ' ';
      }
      std::cout << '\n';
    }
  }

  void step(std::vector<std::vector<Key>> &players, size_t number) {
    for (std::vector<Key> &i : players) {
      for (Key &j : i) {
        if (j.data == number) {
          j.flag = true;
        };
      }
    }
  }

//
  int result_part1(std::vector<std::vector<Key>> &players) {
    for (std::vector<Key> &player : players) {
      int *a = new int[10]{};
      for (auto i = 0; i < player.size(); i++) {
        a[i / 5] += player[i].flag;
      }
      for (auto i = 0; i < player.size(); i++) {
        a[5 + i % 5] += player[i].flag;
      }
      for (int i = 0; i < 10; ++i) {
        if (a[i] == 5) {
          int sum = 0;
          for (Key &p : player) {
            if (!p.flag) {
              sum += p.data;
            }
          }
          return sum;
        }
      }
    }
    return -1;
  }

  int result_part2(std::vector<std::vector<Key>> &players) {
    for (std::vector<Key> &player : players) {
      int *a = new int[10]{};
      for (auto i = 0; i < player.size(); i++) {
        a[i / 5] += player[i].flag;
      }
      for (auto i = 0; i < player.size(); i++) {
        a[5 + i % 5] += player[i].flag;
      }
      for (int i = 0; i < 10; ++i) {
        if (a[i] == 5 && players.size() != 1) {
          players.erase(std::find(players.cbegin(), players.cend(), player));
        } else if (a[i] == 5) {
          int sum = 0;
          for (Key &p : player) {
            if (!p.flag) {
              sum += p.data;
            }
          }
          return sum;
        }
      }
    }
    return -1;
  }

  int main() {
    std::ifstream fin("../data");
    if (!fin.is_open()) {
      return 1;
    }
    std::string data;
    std::getline(fin, data);
    std::vector<size_t> choices;
    char delimiter = ',';
    size_t pos = 0;
    std::string token;
    while ((pos = data.find(delimiter)) != std::string::npos) {
      token = data.substr(0, pos);
      choices.push_back(atoi(token.c_str()));
      data.erase(0, pos + 1);
    }
    choices.push_back(atoi(data.c_str()));
    std::vector<std::vector<Key>> players;

    auto add_key_to_players = [&players, &choices](std::string token, int count) {
      players[count].push_back({.data = (size_t) atoi(token.c_str())});
    };

    delimiter = ' ';
    int count = -1;
    while (std::getline(fin, data)) {
      if (!data.empty()) {
        while ((pos = data.find(delimiter)) != std::string::npos) {
          if (pos == 0) {
            data.erase(0, 1);
            continue;
          }
          token = data.substr(0, pos);
          add_key_to_players(token, count);
          data.erase(0, pos + 1);
        }
        add_key_to_players(data, count);
      } else {
        players.emplace_back();
        count++;
      }
    }

    int res = -1;
    int i = 0;
    for (; i < choices.size() && res == -1; i++) {
      step(players, choices[i]);
      res = result_part2(players);
    }
    std::cout << res * choices[i - 1];
    return 0;
  }
