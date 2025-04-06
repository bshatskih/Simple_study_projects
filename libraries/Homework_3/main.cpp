#include <iostream>
#include "Array.h"
#include "XorArray.h"
#include "SortArray.h"
#include "Application.h"


//!!! Где Application?

int main() {
//    auto *a = new Application();
//    a->run();
  auto *ptr1 = new double[5]{1,2,3,4,5};
  auto *ptr2= new double[10]{12, 12, 3, 12, 1, 9, 7, 5, 5, 12};
  Array *a = new SortArray(5, ptr1);
  Array *b = new SortArray(10, ptr2);
  a->Add(*b);
  a->print();
  return 0;
}
