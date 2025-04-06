#include "Vector.h"

Vector::Vector(int dim, double value) : dim(dim), elements(new double[dim]) {
  for (int i = 0; i < dim; i++) {
    elements[i] = value;
  }
}

Vector::Vector() : dim(0), elements(new double[dim]) {
}

void Vector::print() {
  for (int i = 0; i < dim; i++) {
    std::cout << elements[i] << " ";
  }
  std::cout << std::endl;
}

Vector::Vector(const Vector &other) {
  dim = other.dim;
  elements = new double[dim];
  for (int i = 0; i < dim; ++i) {
    elements[i] = other.elements[i];
  }
}

Vector::~Vector() {
  delete[] elements;
}

Vector& Vector::operator=(const Vector &other) {
  if (this == &other)
    return *this;
    if (dim != other.dim) {
      delete[] elements;
      dim = other.dim;
      elements = new double[dim];
    }
  for (int i = 0; i < dim; ++i) {
    elements[i] = other.elements[i];
  }
  return *this;
}

Vector &Vector::operator+=(const Vector &other) {
  if (dim != other.dim) {
    throw IncompatibleDimException(dim, other.dim);
  }
  for (int i = 0; i < dim; ++i) {
    elements[i] += other.elements[i];
  }
  return *this;
}

Vector &Vector::operator-=(const Vector &other) {
  if (dim != other.dim) {
    throw IncompatibleDimException(dim, other.dim);
  }
  for (int i = 0; i < dim; ++i) {
    elements[i] -= other.elements[i];
  }
  return *this;
}

Vector operator-(Vector other, const Vector &other2) {
  return other -= other2;
}

Vector operator+(Vector other, const Vector &other2) {
  return other += other2;
}

Vector Vector::operator-() {
  Vector c(*this);
  for (int i = 0; i < dim; i++) {
    c.elements[i] = -c.elements[i];
  }
  return c;
}
Vector Vector::operator+() {
  return *this;
}
double &Vector::operator[](const int a) const{
  if (a >= dim)
    throw OutOfRangeException(a, dim);
  return elements[a];
}
std::istream &operator>>(std::istream &is, Vector &other) {
  std::cout << "Input Vector:" << std::endl;
  for (int i = 0; i < other.dim; i++) {
    is >> other.elements[i];
  }
  return is;
}
std::ostream &operator<<(std::ostream &os, const Vector &other) {
  os << "Vector:" << std::endl;
  for (int i = 0; i < other.dim; i++) {
    os << other.elements[i] << " ";
  }
  os << std::endl;
  return os;
}
Vector Vector::operator*(const double a) {
  Vector c(*this);
  for (int i = 0; i < dim; ++i) {
    c.elements[i] *= a;
  }
  return c;
}

Vector operator*(const double a, Vector other) {
  return other * a;
}

double Vector::lenght_vectora() const {
  double lenght = 0;
  for (int i = 0; i < dim; i++) {
    lenght += elements[i] * elements[i];
  }
  return sqrt(lenght);
}
int Vector::dim_vectora() const {
  return dim;
}

double operator*(const Vector &other1, const Vector &other2) {
  if (other1.dim != other2.dim) {
    throw IncompatibleDimException(other1.dim, other2.dim);
  }
  double k = 0;
  for (int i = 0; i < other1.dim; i++) {
    k += other1.elements[i] * other2.elements[i];
  }
  return k;
}

double Vector::element(const int i) const {
  return elements[i];
}

Vector::operator double() const {
  return lenght_vectora();
}


// НЕ ДОЛЖНО БЫТЬ ТАКОГО ОПЕРАТОРА, НЕТ В МАТЕМАТИКЕ ТАКОЙ ОПЕРАЦИИ
// РЕШЕНИЕ ВОПРОСА В ДРУГОМ: В НЕЯВНЫХ ПРЕОБРАЗОВАНИЯХ ВЕКТОРА В ЧИСЛО
// И НАОБОРОТ
// СООБЩЕНИЕ КОМПИЛЯТОР ДОЛЖЕН ВЫВОДИТЬ



