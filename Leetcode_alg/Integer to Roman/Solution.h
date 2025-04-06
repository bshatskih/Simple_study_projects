#pragma once

class Solution {
 public:

  ///I___1\n
  /// V___5\n
  /// X___10\n
  /// L___50\n
  /// C___100\n
  /// D___500\n
  /// M___1000\n

  std::string intToRoman(int num) {
    std::string roman_number;

    while (num > 0) {
      if (num >= 1000 || num / 100 == 9) {
        size_t count_of_M = num / 1000;
        if (count_of_M == 0) {
          num -= 900;
          roman_number += "CM";
        } else {
          num %= 1000;
          for (int i = 0; i < count_of_M; i++) {
            roman_number.push_back('M');
          }
        }
      } else if (num >= 500 || num / 100 == 4) {
        if (num >= 500) {
          num -= 500;
          roman_number.push_back('D');
        } else {
          num -= 400;
          roman_number += "CD";
        }
      } else if (num >= 100 || num / 10 == 9) {
        size_t count_of_C = num / 100;
        if (count_of_C == 0) {
          num -= 90;
          roman_number += "XC";
        } else {
          num %= 100;
          for (int i = 0; i < count_of_C; i++) {
            roman_number.push_back('C');
          }
        }
      } else if (num >= 50 || num / 10 == 4) {
        if (num >= 50) {
          num -= 50;
          roman_number.push_back('L');
        } else {
          num -= 40;
          roman_number += "XL";
        }
      } else if (num >= 10 || num % 10 == 9) {
        size_t count_of_X = num / 10;
        if (count_of_X == 0) {
          num -= 9;
          roman_number += "IX";
        } else {
          num %= 10;
          for (int i = 0; i < count_of_X; i++) {
            roman_number.push_back('X');
          }
        }
      } else if (num >= 5 || num == 4) {
        if (num >= 5) {
          num -= 5;
          roman_number.push_back('V');
        } else {
          num -= 4;
          roman_number += "IV";
        }
      } else {
        for (int i = 0; i < num; i++) {
          roman_number.push_back('I');
        }
        num = 0;
      }
    }
    return roman_number;
  }
};