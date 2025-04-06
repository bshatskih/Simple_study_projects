#pragma once
#include <iostream>
#include <cmath>
#include "exception.h"
#include "Matrix.h"


class Vector {
  int dim;
  double *elements;
 public:
  explicit Vector(int dim, double value = 0);
  Vector(const Vector &other);
  Vector();
  ~Vector();

  Vector& operator=(const Vector &other);
  Vector& operator+=(const Vector &other);
  Vector& operator-=(const Vector &other);
  Vector operator-();
  Vector operator+();
  double& operator[](const int a) const;
  friend std::istream &operator>>(std::istream &is, Vector &other);
  friend std::ostream &operator<<(std::ostream &os, const Vector &other);
  Vector operator*(const double a);
  friend double operator*(const Vector &other1, const Vector &other2);

  friend Vector CSRMatrix::operator*(const Vector &other);

  explicit operator double() const;
  double element(const int i) const;
  double lenght_vectora() const;
  int dim_vectora() const;
  void print();
};

Vector operator+(Vector other, const Vector &other2);
Vector operator-(Vector other, const Vector &other2);
Vector operator*(const double a, Vector other);