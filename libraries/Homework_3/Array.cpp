#include "Array.h"

Array::Array(int size, double value) {
  if (size < 0) {
    throw BadSize("The size of the array must be a positive integer number");
  }
  if (size > max_size) {
    throw BadSize("The size of the array is too large");
  }
  m_size = size;
  elements = new double[m_size];
  for (int i = 0; i < m_size; i++) {
    elements[i] = 0;
  }
}

Array::Array(int size, const double *ptr) {
  if (size < 0) {
    throw BadSize("The size of the array must be a positive integer number");
  }
  if (size > max_size) {
    throw BadSize("The size of the array is too large");
  }
  m_size = size;
  elements = new double[m_size];
  for (int i = 0; i < m_size; i++) {
    elements[i] = ptr[i];
  }
}

Array::Array() : m_size(0), elements(nullptr){}

Array::Array(const Array &other) {
  m_size = other.m_size;
  if (m_size == 0) {
    elements = nullptr;
  }
  else {
    elements = new double[m_size];
    for (int i = 0; i < m_size; i++) {
      elements[i] = other.elements[i];
    }
  }
}

Array::~Array() {
  delete[] elements;
}

int Array::get_size() const {
  return m_size;
}

double Array::operator[](const int &index) const {
  if (index >= m_size || index < 0)
    throw OutOfRange("Array::operator[]");
  return elements[index];
}

double &Array::operator[](const int &index) {
  if (index >= m_size || index < 0)
    throw OutOfRange("Array::operator[]");
  return elements[index];
}


