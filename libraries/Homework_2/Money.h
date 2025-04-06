#pragma once
#include "Array.h"
#include <vector>
#include <sstream>
#include "cstring"

class Money : public Array {
  bool sign = true;
 public:
  Money(bool flag, int rubles, int kopeks);
  explicit Money(const std::string &);
  explicit Money(const double &);
  Money(const Money &) = default;
  Money() = default;

  void Add(const Array *other, Array *result) override;
  void print() override;
  Money Subtract(const Money &other) const;
  Money Multiply(const Money &other) const;
  Money Multiply(float ) const;
  Money Divide(const Money &other) const;
  Money Divide(float ) const;
  bool operator>(const Money &other) const;
  bool operator>=(const Money &other) const;
  bool operator==(const Money &other) const;
  bool operator<(const Money &other) const;
  bool operator<=(const Money &other) const;
  friend std::ostream &operator<<(std::ostream &os, const Money &other);
  friend std::istream &operator>>(std::istream &is, Money &other);

  int to_sum() const;
  float to_sumF() const;
};

int lenght_v(int );
int lenght_s(const std::string &);
