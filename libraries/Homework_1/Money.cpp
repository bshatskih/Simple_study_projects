#include "Money.h"
#include "LongLong.h"

int Money::ExistMoney = 0;

//!!! Объекты (rubles) передаются по ссылке на константу
Money::Money(const LongLong &rub, unsigned char kopeks) : rubles(rub), kopeks(kopeks) {
  ExistMoney++;
}

//!!! Между методами оставляют 1-2 строки - отформатируйте код

Money::Money() : rubles(0), kopeks(0) {
  ExistMoney++;
}

Money::Money(const double &rubles)
    : rubles(static_cast<unsigned long >(rubles)), kopeks(static_cast<unsigned long >(rubles * 100) % 100) {
  ExistMoney++;
}

Money::Money(const std::string &money) {
  std::vector<int> vector;
  std::istringstream iss(money);
  std::string string;
  int value;
  while (std::getline(iss, string, ',')) {
    std::stringstream ss;
    ss << string;
    ss >> value;
    vector.push_back(value);
  }
  rubles = vector[0];
  kopeks = vector[1];
  ExistMoney++;
}

Money::~Money() {
  ExistMoney--;
}

//!!! Чем не устраивает версия, создаваемая компилитором?
Money::Money(const Money &other) : rubles(other.rubles), kopeks(other.kopeks) {
//!!! Эти присваивания лучше делать через список инициализаторов конструктора (двоеточие)
  ExistMoney++;
}

Money &Money::operator+=(const Money &other) {
  kopeks += other.kopeks;
  rubles += other.rubles;
  if (kopeks >= 100) {
    kopeks -= 100;
    rubles += static_cast<LongLong>(1);
  }
  return *this;
}

Money &Money::operator-=(const Money &other) {
  rubles -= other.rubles;
  if (kopeks < other.kopeks) {
    kopeks = kopeks + 100 - other.kopeks;
    rubles -= static_cast<LongLong>(1);
  }
  return *this;
}
bool Money::operator<(const Money &other) const {
  if (rubles == other.rubles)
    return kopeks < other.kopeks;
  return rubles < other.rubles;
}
bool Money::operator==(const Money &other) const {
  return rubles == other.rubles && kopeks == other.kopeks;
}
bool Money::operator<=(const Money &other) const {
  return *this < other || *this == other;
}
bool Money::operator>(const Money &other) const {
  return !(*this < other) && !(*this == other);
}
bool Money::operator>=(const Money &other) const {
  return *this > other || *this == other;
}
Money &Money::operator/=(const Money &other) {
  if (other.rubles.toLongLong() == 0)
    throw OutOfRangeException();
  long total1 = rubles.toLongLong() * 100 + (long) kopeks;
  long total2 = other.rubles.toLongLong() * 100 + (long) other.kopeks;
  rubles = total1 / total2;
  kopeks = ((total1*100) / total2) % 100;
  return *this;
}
std::ostream &operator<<(std::ostream &os, const Money &other) {
  if ((int) other.kopeks < 10)
    os << other.rubles.toLongLong() << ",0" << (int) other.kopeks << std::endl;
  else
    os << other.rubles.toLongLong() << "," << (int) other.kopeks << std::endl;
  return os;
}

std::istream &operator>>(std::istream &is, Money &other) {
  std::cout << "Enter the amount: rubles , kopecks" << std::endl;
  char c;
  int kopek;
  is >> other.rubles >> c >> kopek;
  other.kopeks = static_cast<unsigned char>(kopek);
  return is;
}

Money &Money::operator/=(const float &other) {
  if (other < 0)
    throw IncompatibleDimException(other);
  if (other == 0)
    throw OutOfRangeException();
  long total1 = rubles.toLongLong() * 100 + (long) kopeks;
  rubles = (long) (total1 / other) / 100;
  kopeks = (long) (total1 / other) % 100;
  return *this;
}
Money &Money::operator*=(const float &other) {
  if (other < 0)
    throw IncompatibleDimException(other);
  long total1 = rubles.toLongLong() * 100 + (long) kopeks;
  rubles = (long) (total1 * other) / 100;
  kopeks = (long) (total1 * other) % 100;
  return *this;
}

Money &Money::operator*=(const Money &other) {
  long total1 = rubles.toLongLong() * 100 + (long) kopeks;
  rubles = (long) (total1 * other.rubles.toLongLong()) / 100;
  kopeks = (long) (total1 * other.kopeks) % 100;
  return *this;
}

Money Money::kopeksToMoney(const unsigned long &kopeks) {
  if (kopeks < 0)
    throw IncompatibleDimException((float)kopeks);
  Money amount(static_cast<LongLong>(kopeks / 100), kopeks % 100);
  ExistMoney++;
  return amount;
}

Money operator-(Money other1, const Money &other2) {
  return other1 -= other2;
}

Money operator+(Money other1, const Money &other2) {
  return other1 += other2;
}

Money operator/(Money other1, const Money &other2) {
  return other1 /= other2;
}

Money operator/(Money other1, const float &other2) {
  return other1 /= other2;
}

Money operator*(Money other1, const float &other2) {
  return other1 *= other2;
}

Money operator*(Money other1, const Money &other2) {
  return other1 *= other2;
}

unsigned long Money::get_rubles() const {
  return rubles.toLongLong();
}

int Money::get_kopeks() const {
  return kopeks;
}

int Money::get_ExistMoney(){
  return ExistMoney;
}

void Money::set_kopeks(const int &kop) {
  if (kop < 0)
    throw IncompatibleDimException((float)kop);
  kopeks = kop;
}

void Money::set_rubles(const unsigned long &rub) {
  if (rub < 0)
    throw IncompatibleDimException((float)rub);
  rubles = rub;
}

