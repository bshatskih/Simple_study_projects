#ifndef HOMEWORK_3__SORTARRAY_H_
#define HOMEWORK_3__SORTARRAY_H_
#include "Array.h"
#include <iomanip>

class SortArray : public Array{
 public:
  explicit SortArray(int size) : Array(size) {};
  explicit SortArray(int size, const double  *ptr) : Array(size, ptr) {};
  SortArray(): Array() {};

  void Add(const Array &other) override;
  void Sort(const double &a) override;
  void print() override;
  void enter() override;
  SortArray &operator=(const SortArray &other);

  int search_element(double a);
  int search_element_e(double a, int i_0);
};

#endif
