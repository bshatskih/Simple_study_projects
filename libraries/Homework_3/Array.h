#pragma once
#include <iostream>
#include "Exception.h"

class Array {
 protected:
  static const int max_size = 100;
  int m_size;
  double *elements;

 public:
  explicit Array(int size, double value = 0);
  explicit Array(int size, const double *ptr);
  Array(const Array &other);
  Array();
  virtual ~Array(); //!!! Почему деструктор не виртуальный?

  virtual void Add(const Array &other) = 0;
  virtual void Sort(const double &a) = 0;
  virtual void print() = 0;
  virtual void enter() = 0;

  //!!! Должно быть 2 версии.
  double operator[](const int &index) const; //!!! Где const у возвращаемого типа.
  double &operator[](const int &index);
  int get_size() const;
};

