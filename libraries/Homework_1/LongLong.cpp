#include "LongLong.h"

int LongLong::ExistLongLong = 0;

LongLong::LongLong(unsigned long rubles) {
  starsh = rubles / 1000000;
  mladsh = rubles % 1000000;
  ExistLongLong++;
}

LongLong::LongLong() : starsh(0), mladsh(0) {
  ExistLongLong++;
}

//!!! Чем не устраивает версия конструктора копирования, создаваемая компилятором?
LongLong::LongLong(const LongLong &other) : mladsh(other.mladsh),   starsh(other.starsh) {
  ExistLongLong++;
}


LongLong::~LongLong() {
  ExistLongLong--;
}


LongLong &LongLong::operator+=(const LongLong &other) {
  starsh += other.starsh;
  if (mladsh + other.mladsh >= 1000000) {
    starsh++;
    mladsh += other.mladsh - 1000000;
  } else {
    mladsh += other.mladsh;
  }
  return *this;
}

LongLong &LongLong::operator-=(const LongLong &other) {
  starsh -= other.starsh;
  if (mladsh < other.mladsh) {
    mladsh -= other.mladsh + 1000000;
    starsh--;
  } else {
    mladsh -= other.mladsh;
  }
  return *this;
}

//!!! Чем не устраивает версия =, создаваемая компилятором?
LongLong &LongLong::operator=(const LongLong &other) {

//!! А если создали, где проверка на самоприсваивание?
  if (*this == other)
    return *this;
  mladsh = other.mladsh;
  starsh = other.starsh;
  return *this;
}

LongLong &LongLong::operator=(const unsigned long &rubles) {
  starsh = rubles / 1000000;
  mladsh = rubles % 1000000;
  return *this;
}

bool LongLong::operator<(const LongLong &other) const {
  if (starsh == other.starsh)
    return mladsh < other.mladsh;
  return starsh < other.starsh;
}

bool LongLong::operator==(const LongLong &other) const {
  return starsh == other.starsh && mladsh == other.mladsh;
}
bool LongLong::operator>(const LongLong &other) const {
  return !(*this < other) && !(*this == other);
}
bool LongLong::operator>=(const LongLong &other) const {
  return *this > other || *this == other;
}
bool LongLong::operator<=(const LongLong &other) const {
  return *this < other || *this == other;
}
long LongLong::toLongLong() const {
  return starsh * 1000000 + mladsh;
}

LongLong operator+(LongLong other1, const LongLong &other2) {
  return other1 += other2;
}
LongLong operator-(LongLong other1, const LongLong &other2) {
  return other1 -= other2;
}

int LongLong::get_ExistLongLong(){
  return ExistLongLong;
}
std::istream &operator>>(std::istream &is, LongLong &other) {
  unsigned long rubles;
  is >> rubles;
  other.starsh = rubles/1000000;
  other.mladsh = rubles%1000000;
  return is;
}
std::ostream &operator<<(std::ostream &os, const LongLong &other) {
  os << other.toLongLong();
  std::cout << std::endl;
  return os;
}
