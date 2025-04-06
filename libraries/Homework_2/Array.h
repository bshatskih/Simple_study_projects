#pragma once
#include "exception.h"
#include <iostream>

class Array {
 protected:
  static const int max_size = 100;
  unsigned char *array;
  int m_size;

 public:
  explicit Array(int size, int value = 0); //!!! Запретите неявные преобразования
  explicit Array(int size, const unsigned char *ptr);
  explicit Array(const std::string &);
  Array(const Array &other);
  Array();
  virtual ~Array();
  //!!! Где виртуальный деструктор?

  unsigned char &operator[](const int &index);
  unsigned char operator[](const int &index) const;
  Array &operator=(const Array &other);


  //!!! Сигнатура этого метода должны выглядеть так virtual void Add(const Array *other, Array *result);
  virtual void Add(const Array *other, Array *result);
  virtual void print();
  friend std::istream &operator>>(std::istream &is, Array &other);
  friend std::ostream &operator<<(std::ostream &os, const Array &other);

  int get_size() const;
  void add_size(int );
  void set_size(int );
};
