#include "XorArray.h"

void XorArray::enter() {
  std::cout << "Enter size of XorArray:" << std::endl;
  int size;
  std::cin >> size;
  if (size < 0) {
    throw BadSize("The size of the array must be a positive integer number");
  }
  if (size > max_size) {
    throw BadSize("The size of the array is too large");
  }
  m_size = size;
  elements = new double[m_size];
  std::cout << "Enter XorArray:" << std::endl;
  for (int i = 0; i < m_size; i++) {
    std::cin >> elements[i];
  }
}

void XorArray::print() {
  std::cout << "XorArray:" << std::endl;
  for (int i = 0; i < m_size; i++) {
    std::cout << std::fixed << std::setprecision(1) << elements[i] << ' ';
  }
  std::cout << std::endl;
}

void XorArray::Add(const Array &other) {
  if (m_size >= other.get_size()) {
    for (int i = 0; i < other.get_size(); i++) {
      elements[i] += other[i];
    }
  } else {
    auto mas = new double[m_size];
    for (int i = 0; i < m_size; i++) {
      mas[i] = elements[i];
    }
    delete[] elements;
    elements = new double[other.get_size()];
    for (int i = 0; i < other.get_size(); i++) {
      elements[i] = other[i];
    }
    for (int i = 0; i < m_size; i++) {
      elements[i] += mas[i];
    }
    delete[] mas;
    m_size = other.get_size();
  }
}

void XorArray::Sort(const double &a) {
  bool p = false;
  if (a - (int) a == 0 && (int) a % 2 == 0) {
    p = true;
  }
  for (int i = 0; i < m_size; i++) {
    if (p && elements[i] < 0) {
      throw MathException("It is impossible to extract a root multiple of two from a negative number");
    }
    elements[i] = pow(elements[i], (double) 1 / a);
  }
}

XorArray &XorArray::operator=(const XorArray &other) {
  if (this == &other) {
    return *this;
  }
  if (m_size != other.m_size) {
    delete[] elements;
    m_size = other.m_size;
    elements = new double[m_size];
  }
  for (int i = 0; i < m_size; ++i) {
    elements[i] = other.elements[i];
  }
  return *this;
}

