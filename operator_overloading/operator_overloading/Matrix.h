#pragma once
#include <iostream>

class Vector;

class CSRMatrix {
  int n;
  int m;
  int nnz;
  double *elements_m;
  int *index_st;
  int *index_str;
 public:
  CSRMatrix();
  CSRMatrix(int n, int m, int nnz, double *elements_m0, int *index_st0, int *index_str0);
  CSRMatrix(int n, int m, int nnz);
  CSRMatrix(const CSRMatrix &other);
  ~CSRMatrix();

  CSRMatrix operator*(const double a);
  friend std::istream &operator>>(std::istream &is, CSRMatrix &other);
  friend std::ostream &operator<<(std::ostream &os, const CSRMatrix &other);
  Vector operator*(const Vector &other);

  void print();
  int quantity_nul();
  void dimension_matrix();
  int dim_m() const;
  int dim_n() const;
};

CSRMatrix operator*(const double a, CSRMatrix other);
