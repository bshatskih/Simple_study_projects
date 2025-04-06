#include <iostream>
#include <fstream>
#include <vector>

struct Monkey {
  std::vector<size_t> items;
  size_t operation_value{};
  char operation_sign{};
  size_t division_value{};
  short true_test{};
  short false_test{};
  size_t count = 0;
};

void input_item(std::vector<size_t> &item, std::string &str, size_t pos) {
  size_t ch;
  while (pos < str.size()) {
    ch = str[pos] - '0';
    pos++;
    while (isdigit(str[pos])) {
      ch = ch * 10 + str[pos] - '0';
      pos++;
    }
    item.push_back(ch);
    pos += 2;
  }
}

size_t string_to_int(std::string &str, size_t pos) {
  std::string answer;
  answer.append(str, pos);
  return atoi(answer.c_str());
}

void print_herd(std::vector<Monkey> &herd) {
  for (int i = 0; i < herd.size(); i++) {
    std::cout << "Monkey " << i << ':' << '\n';
    std::cout << "  Starting items: ";
    if (herd[i].items.size() >= 2) {
      for (int j = 0; j < herd[i].items.size() - 1; j++) {
        std::cout << herd[i].items[j] << ", ";
      }
      std::cout << herd[i].items[herd[i].items.size() - 1] << '\n';
    } else if (herd[i].items.size() == 1) {
      std::cout << herd[i].items[0] << '\n';
    } else {
      std::cout << '\n';
    }
    std::cout << "  Operation: new = old " << herd[i].operation_sign << ' ' << herd[i].operation_value << '\n';
    std::cout << "  Test: divisible by " << herd[i].division_value << '\n';
    std::cout << "    If true: throw to monkey " << herd[i].true_test << '\n';
    std::cout << "    If false: throw to monkey " << herd[i].false_test << '\n';
    std::cout << '\n' << '\n';
  }
}

int main() {
  std::ifstream fin("../test");
  std::string str;
  if (!fin.is_open()) {
    std::cout << "error";
  }
  std::vector<Monkey> herd;

  size_t index = 0;
  while (std::getline(fin, str)) {
    if (str.empty() || str[0] == 'M')
      continue;
    else
      herd.emplace_back();
    input_item(herd[index].items, str, 18);
    std::getline(fin, str);
    if (isdigit(str[25])) {
      herd[index].operation_value = string_to_int(str, 25);
    } else {
      herd[index].operation_value = 0;
    }
    herd[index].operation_sign = str[23];
    std::getline(fin, str);
    herd[index].division_value = string_to_int(str, 21);
    std::getline(fin, str);
    herd[index].true_test = static_cast<short >(string_to_int(str, 29));
    std::getline(fin, str);
    herd[index].false_test = static_cast<short >(string_to_int(str, 30));
    index++;
  }

  unsigned int ch = 1;
  for (int i = 0; i < herd.size(); i++) {
    ch *= herd[i].division_value;
  }

  for (int i = 0; i < 10000; i++) {

    for (size_t j = 0; j < herd.size(); j++) {

      for (int k = herd[j].items.size() - 1; k >= 0; k--) {
        herd[j].count++;
        if (herd[j].operation_sign == '+') {
          if (herd[j].operation_value == 0) {
            herd[j].items[k] += herd[j].items[k];
          } else {
            herd[j].items[k] += herd[j].operation_value;
          }
        } else {
          if (herd[j].operation_value == 0) {
            herd[j].items[k] *= herd[j].items[k];
          } else {
            herd[j].items[k] *= herd[j].operation_value;
          }
        }
        herd[j].items[k] %= ch;
        if (herd[j].items[k] % herd[j].division_value == 0) {
          herd[herd[j].true_test].items.push_back(herd[j].items[k]);
        } else {
          herd[herd[j].false_test].items.push_back(herd[j].items[k]);
        }
        herd[j].items.pop_back();
      }
    }
  }
  size_t max1 = herd[0].count;
  size_t max2 = herd[1].count;
  if (max1 > max2) {
    std::swap(max1, max2);
  }

//  print_herd(herd);
  for (int i = 2; i < herd.size(); i++) {
    if (herd[i].count > max1) {
      if (herd[i].count > max2) {
        max1 = max2;
        max2 = herd[i].count;
      } else {
        max1 = herd[i].count;
      }
    }
  }
  std::cout << '\n';
  std::cout << max1 * max2;
  return 0;
}
