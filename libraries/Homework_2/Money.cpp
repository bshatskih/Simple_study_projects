#include "Money.h"

Money::Money(bool flag, int rubles, int kopeks) : Array(2 + lenght_v(rubles)), sign(flag) {
  array[0] = kopeks % 10;
  array[1] = kopeks / 10;
  int len = lenght_v(rubles);
  for (int i = 0; i < len; i++) {
    array[i + 2] = rubles % 10;
    rubles /= 10;
  }
}

Money::Money(const double &money) : Array(lenght_v((int) money) + 2) {
  std::string buffer = std::to_string(money);
  int index = (int)buffer.find('.');
  std::string temp;
  temp.assign(buffer, index + 1, 2);
  array[0] = temp[1] - '0';
  array[1] = temp[0] - '0';
  int k = 1;
  if (buffer[0] != '-') {
    sign = true;
    for (int i = index - 1; i >= 0; i--) {
      array[++k] = buffer[i] - '0';
    }
  } else {
    sign = false;
    for (int i = index - 1; i >= 1; i--) {
      array[++k] = buffer[i] - '0';
    }
  }
}

Money::Money(const std::string &money) : Array(lenght_s(money)) {
  int index = (int)money.find(',');
  std::string temp;
  temp.assign(money, index + 1, 2);
  array[0] = temp[1] - '0';
  array[1] = temp[0] - '0';
  int k = 1;
  if (money[0] != '-') {
    sign = true;
    for (int i = index - 1; i >= 0; i--) {
      array[++k] = money[i] - '0';
    }
  } else {
    sign = false;
    for (int i = index - 1; i >= 1; i--) {
      array[++k] = money[i] - '0';
    }
  }
  for (int i = 0; i < m_size; i++) {
    if (strchr("1234567890", array[i] + '0') == nullptr) {
      delete[] array;
      throw std::exception();
    }
  }
}

void Money::Add(const Array *other, Array *result) {
  const auto *other_1 = dynamic_cast<const Money *>(other);
  if (other_1 == nullptr) {
    throw CastError("MoneySum #1");
  }
  auto *result_1 = dynamic_cast<Money *>(result);
  if (result_1 == nullptr) {
    throw CastError("MoneySum #2");
  }
  *result_1 = Money(to_sumF() + other_1->to_sumF());
}

Money Money::Subtract(const Money &other) const {
  if (!other.to_sum()) {
    throw MathException("Substract");
  }
  return Money(to_sumF()-other.to_sumF());
}

Money Money::Multiply(const Money &other) const{
  if (!other.to_sum()) {
    throw MathException("Multiply");
  }
  return Money(to_sumF()*other.to_sumF());
}

Money Money::Multiply(float value) const {
  if (value == 0) {
    throw MathException("Multiply nomber");
  }
  return Money(to_sumF()*value);
}

Money Money::Divide(const Money &other) const{
  if (!other.to_sum()) {
    throw MathException("Divide");
  }
  return Money(to_sumF()/other.to_sumF());
}

Money Money::Divide(float value) const{
  if (value == 0) {
    throw MathException("Divide nomber");
  }
  return Money(to_sumF()/value);
}

void Money::print() {
  std::cout << "Summa:" << std::endl;
  if (!sign) {
    std::cout << '-';
  }
  bool g = true;
  for (int i = m_size - 1; i > 1; i--) {
    std::cout << (int) array[i];
    if (array[i] != 0) {
      g = false;
    }
  }
  if (g) {
    std::cout << "0";
  }
  std::cout << "," << (int) array[1] << (int) array[0] << std::endl;
}

int lenght_v(int rubles) {
  int len = 0;
  while (rubles != 0) {
    rubles /= 10;
    len++;
  }
  return len;
}

bool Money::operator>(const Money &other) const {
  return to_sum() > other.to_sum();
}

bool Money::operator>=(const Money &other) const {
  return *this > other || *this == other;
}

bool Money::operator==(const Money &other) const {
  return to_sum() == other.to_sum();
}

bool Money::operator<(const Money &other) const {
  return !(*this > other) && !(*this == other);
}

bool Money::operator<=(const Money &other) const {
  return !(*this > other);
}

int lenght_s(const std::string &str) {
  if (str[0] == '-') {
    return (int)str.length() - 2;
  }
  return (int)str.length() - 1;
}

int Money::to_sum() const {
  int sum = 0;
  int p = 1;
  for (int i = 0; i < get_size(); i++) {
    sum += array[i] * p;
    p *= 10;
  }
  return sum;
}

std::ostream &operator<<(std::ostream &os, const Money &other) {
  if (!other.sign) {
    std::cout << '-';
  }
  bool g = true;
  for (int i = other.m_size - 1; i > 1; i--) {
    std::cout << (int) other.array[i];
    if (other.array[i] != 0) {
      g = false;
    }
  }
  if (g) {
    std::cout << "0";
  }
  std::cout << "," << (int) other.array[1] << (int) other.array[0];
  return os;
}

std::istream &operator>>(std::istream &is, Money &other) {
  std::cout << "Enter the amount: rubles,kopecks" << std::endl;
  std::string money;
  is >> money;
  int index = (int)money.find(',');
  std::string temp;
  temp.assign(money, index + 1, 2);
  other.m_size = lenght_s(money);
  if (other.m_size > Money::max_size) {
    throw OutOfRange("Fraction std::cin");
  }
  delete[] other.array;
  other.array = new unsigned char[other.m_size];
  other[0] = temp[1] - '0';
  other[1] = temp[0] - '0';
  int k = 1;
  if (money[0] == '-') {
    other.sign = false;
    for (int i = index - 1; i > 0; i--) {
      other[++k] = money[i] - '0';
    }
  }
  else {
    for (int i = index - 1; i >= 0; i--) {
      other[++k] = money[i] - '0';
    }
  }
  for (int i = 0; i < other.m_size; i++) {
    if (strchr("1234567890", other[i] + '0') == nullptr) {
      delete[] other.array;
      throw std::exception();
    }
  }
  return is;
}

float Money::to_sumF() const {
  int sum = 0;
  int p = 1;
  for (int i = 0; i < get_size(); i++) {
    sum += array[i] * p;
    p *= 10;
  }
  if (!sign) {
    sum *= -1;
  }
  return (float)sum/100;
}