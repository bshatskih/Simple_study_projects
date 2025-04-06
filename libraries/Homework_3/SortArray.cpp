#include "SortArray.h"

void SortArray::Add(const Array &other) {
  auto *mas = new double[m_size];         //!! Где delete?
  int k = 0;
  bool flag = false;
  for (int i = 0; i < m_size; i++) {
    if (search_element_e(elements[i], i)) {
      mas[k++] = elements[i];
    }
    else {
      for (int j = 0; j < k; j++) {
        if (mas[j] == elements[i]) {
          flag = true;
        }
      }
      if (!flag) {
        mas[k++] = elements[i];
      }
      flag = false;
    }
  }
  int u = 0;
  flag = true;
  auto *mas_1 = new double[other.get_size()];
  for (int i = 0; i < other.get_size(); i++) {
    for (int j = 0; j < other.get_size(); j++) {
      if (other[i] == other[j] && i != j) {
        flag = false;
      }
    }
    if (flag) {
      mas_1[u++] = other[i];
    } else {
      for (int o = 0; o < u; o++) {
        if (mas_1[o] == other[i]) {
          flag = true;
        }
      }
      if (!flag) {
        mas_1[u++] = other[i];
      }
    }
    flag = true;
  }
  int p = 0;
  for (int i = 0; i < u; i++) {
    p += search_element(mas_1[i]);
  }
  if (p == 0) {
    delete[] elements;
    elements = mas;
    m_size = k;
    return;
  }
  else {
    m_size = p + k;
    delete[] elements;
    elements = new double[m_size];
    for (int i = 0; i < k; i++) {
      elements[i] = mas[i];
    }
    delete[] mas;
    for (int i = 0; i < u; i++) {
      if (search_element(mas_1[i])) {
        elements[m_size - (p--)] = mas_1[i];
      }
    }
  }
  delete[] mas_1;
}

int SortArray::search_element_e(double a, int i_0) {
  int f = 1;
  for (int i = 0; i < m_size; i++) {
    if (a == elements[i] && i != i_0) {
      f = 0;
    }
  }
  return f;
}

int SortArray::search_element(double a) {
  int f = 1;
  for (int i = 0; i < m_size; i++) {
    if (a == elements[i]) {
      f = 0;
    }
  }
  return f;
}

void SortArray::enter() {
  std::cout << "Enter size of SortArray:" << std::endl;
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
  std::cout << "Enter SortArray:" << std::endl;
  for (int i = 0; i < m_size; i++) {
    std::cin >> elements[i];
  }
}

void SortArray::print() {
  std::cout << "SortArray:" << std::endl;
  for (int i = 0; i < m_size; i++) {
    std::cout << std::fixed << std::setprecision(0) << elements[i] << ' ';
  }
  std::cout << std::endl;
}

void SortArray::Sort(const double &a) {
  if (a == 1) {
    double t = 0;
    for (int i = 0; i < m_size; i++) {
      for (int j = (m_size - 1); j >= (i + 1); j--) {
        if (elements[j] < elements[j - 1]) {
          t = elements[j];
          elements[j] = elements[j - 1];
          elements[j - 1] = t;
        }
      }
    }
  }
  else if (a == -1) {
    double t = 0;
    for (int i = 0; i < m_size; i++) {
      for (int j = (m_size - 1); j >= (i + 1); j--) {
        if (elements[j] > elements[j - 1]) {
          t = elements[j];
          elements[j] = elements[j - 1];
          elements[j - 1] = t;
        }
      }
    }
  }
  else {
    std::cout << "Error!\n"
                 "1 - ascending sort\n"
                 "-1 - descending sort\n" << std::endl;
  }
}

SortArray &SortArray::operator=(const SortArray &other) {
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
