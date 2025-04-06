#include <iostream>
#include "Vector.h"
#include "Matrix.h"

int main() {
  Vector a_0(4, 15);
  double f = (double)a_0;
  std::cout<<f;
  /*
  Vector b_0(4,1);
  Vector c_0(5, 1);
  /*std::cin >> a_0;
  std::cout << a_0;
  std::cin >> c_0;
  std::cout << c_0;
  double a[] = {1, 2, 3, 4, 1, 11};
  int b[] = {0, 1, 3, 2, 1, 3};
  int c[] = {0, 3, 4, 6};
  CSRMatrix A(6, 6, 4, a, b, c);

  try {
    a_0[10];
  }
  catch (std::exception &e){
    std::cout << e.what();
  }
  try {
    double t = a_0*b_0;
  }
  catch (std::exception &e){
    std::cout << e.what();
  }
  try {
    a_0 += b_0;
  }
  catch (std::exception &e){
    std::cout << e.what();
  }
  try {
    a_0 -= b_0;
  }
  catch (std::exception &e){
    std::cout << e.what();
  }
  try {
    a_0 = A*c_0;
  }
  catch (std::exception &e){
    std::cout << e.what();
  }

  CSRMatrix C(10, 10, 5);
  std::cin >> C;
  std::cout << C;
  Vector res = -3*C * (a_0-2*c_0)+b_0*5;
  res.print();*/
}
