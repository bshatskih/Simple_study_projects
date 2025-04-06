#pragma once
#include <iostream>

class LongLong {
  unsigned long starsh;
  unsigned long mladsh;
  static int ExistLongLong;

 public:
  explicit LongLong(unsigned long); //!!! Запретите неявные преобразования
  LongLong();
  LongLong(const LongLong &other);
  ~LongLong();

  LongLong &operator=(const unsigned long &);
  LongLong &operator=(const LongLong &other);
  LongLong &operator+=(const LongLong &other);
  LongLong &operator-=(const LongLong &other);
  bool operator<(const LongLong &other) const;
  bool operator==(const LongLong &other) const;
  bool operator>(const LongLong &other) const;
  bool operator>=(const LongLong &other) const;
  bool operator<=(const LongLong &other) const;
  friend std::istream &operator>>(std::istream &is, LongLong &other);
  friend std::ostream &operator<<(std::ostream &os, const LongLong &other);

  long toLongLong() const;
  static int get_ExistLongLong();
};

LongLong operator+(LongLong other1, const LongLong &other2);
LongLong operator-(LongLong other1, const LongLong &other2);