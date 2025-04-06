#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include "LongLong.h"
#include "Exception.h"

class LongLong;

class Money {
  LongLong rubles;
  unsigned char kopeks;
  static int ExistMoney;

 public:
  Money(const LongLong &, unsigned char);
  Money();
  explicit Money(const std::string &);
  explicit Money(const double &);
  Money(const Money &other);
  ~Money();

  static Money kopeksToMoney(const unsigned long &);
  bool operator<(const Money &other) const;
  bool operator==(const Money &other) const;
  bool operator<=(const Money &other) const;
  bool operator>(const Money &other) const;
  bool operator>=(const Money &other) const;
  Money &operator+=(const Money &other);
  Money &operator-=(const Money &other);
  Money &operator/=(const Money &other);
  Money &operator/=(const float &other);
  Money &operator*=(const float &other);
  Money &operator*=(const Money &other);
  friend std::ostream &operator<<(std::ostream &os, const Money &other);
  friend std::istream &operator>>(std::istream &is, Money &other);

  unsigned long get_rubles() const;
  int get_kopeks() const;
  static int get_ExistMoney();
  void set_rubles(const unsigned long &);
  void set_kopeks(const int &);

};

Money operator-(Money other1, const Money &other2);
Money operator+(Money other1, const Money &other2);
Money operator/(Money other1, const Money &other2);
Money operator/(Money other1, const float &other2);
Money operator*(Money other1, const float &other2);
Money operator*(Money other1, const Money &other2);
