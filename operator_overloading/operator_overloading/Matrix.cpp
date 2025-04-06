#include "Matrix.h"
#include "Vector.h"

CSRMatrix::CSRMatrix(int n, int m, int nnz, double *elements_m0, int *index_st0, int *index_str0)
    : n(n), m(m), nnz(nnz), elements_m(new double[n]), index_st(new int[m]), index_str(new int[nnz]) {
  for (int i = 0; i < n; i++) {
    elements_m[i] = elements_m0[i];
  }
  for (int i = 0; i < m; i++) {
    index_st[i] = index_st0[i];
  }
  for (int i = 0; i < nnz; i++) {
    index_str[i] = index_str0[i];
  }
}
CSRMatrix::CSRMatrix(const CSRMatrix &other) :
    CSRMatrix(other.n, other.m, other.nnz, other.elements_m, other.index_st, other.index_str){
}
CSRMatrix::~CSRMatrix() {
  delete[] elements_m;
  delete[] index_st;
  delete[] index_str;
}
CSRMatrix::CSRMatrix() : n(0), m(0), nnz(0), elements_m(new double[n]), index_st(new int[m]), index_str(new int[nnz]){
}

CSRMatrix::CSRMatrix(int n, int m, int nnz) : n(n), m(m), nnz(nnz), elements_m(new double[n]), index_st(new int[m]), index_str(new int[nnz]) {
}

void CSRMatrix::print() {
  std::cout << "Matrix:" << std::endl;
  int max = this->dim_m();

  double **matrix = new double *[nnz - 1];
  for (int i = 0; i < nnz - 1; i++) {
    matrix[i] = new double[max];
  }
  int k = 0;
  for (int i = 0; i < nnz - 1; i++)
    for (int j = 0; j < max; j++) {
      if (j == index_st[k]) {
        matrix[i][j] = elements_m[k];
        k++;
      } else {
        matrix[i][j] = 0;
      }
    }
  for (int i = 0; i < nnz - 1; i++) {
    for (int j = 0; j < max; j++) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
  for (int i = 0; i < nnz - 1; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

CSRMatrix CSRMatrix::operator*(const double a) {
  CSRMatrix res(*this);
  for (int i = 0; i < n; i++) {
    res.elements_m[i] *= a;
  }
  return res;
}

std::istream &operator>>(std::istream &is, CSRMatrix &other) {
  std::cout << std::endl;
  std::cout << "Input Matrix:" << std::endl;
  for (int i = 0; i < other.n; i++) {
    is >> other.elements_m[i];
  }
  for (int i = 0; i < other.m; i++) {
    is >> other.index_st[i];
  }
  for (int i = 0; i < other.nnz; i++) {
    is >> other.index_str[i];
  }
  std::cout << std::endl;
  return  is;
}

std::ostream &operator<<(std::ostream &os, const CSRMatrix &other) {
  os << "Matrix:" << std::endl;
  double max = -1000;
  for (int i = 0; i < other.m; i++) {
    if (other.index_st[i] >= max) {
      max = other.index_st[i];
    }
  }
  double **matrix = new double *[other.nnz - 1];
  for (int i = 0; i < other.nnz - 1; i++) {
    matrix[i] = new double[(int) max + 1];
  }
  int k = 0;
  for (int i = 0; i < other.nnz - 1; i++)
    for (int j = 0; j <= (int) max; j++) {
      if (j == other.index_st[k]) {
        matrix[i][j] = other.elements_m[k];
        k++;
      } else {
        matrix[i][j] = 0;
      }
    }
  for (int i = 0; i < other.nnz - 1; i++) {
    for (int j = 0; j <= (int) max; j++) {
      os << matrix[i][j] << " ";
    }
    os << std::endl;
  }
  for (int i = 0; i < other.nnz - 1; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
  return os;
}

int CSRMatrix::quantity_nul() {
  double max = -1000;
  for (int i = 0; i < m; i++) {
    if (index_st[i] >= max) {
      max = index_st[i];
    }
  }
  return (nnz - 1) * ((int) max + 1) - n;
}

void CSRMatrix::dimension_matrix() {
  double max = -1000;
  for (int i = 0; i < m; i++) {
    if (index_st[i] >= max) {
      max = index_st[i];
    }
  }
  std::cout << nnz - 1 << "*" << (int) max + 1 << std::endl;
}

// ВЕРНИ КОНСТАНТНУЮ ССЫЛКУ, КОПИРОВАНИЕ - ДОРОГАЯ ОПЕРАЦИЯ,
// В ДАННОМ СЛУЧАЕ КОПИРОВАНИЕ ИЗЛИШНЕ
// РЕШЕНИЕ ПРОБЛЕМЫ В ДРУГОМ МЕСТЕ
Vector CSRMatrix::operator*(const Vector &other) {
  int max = this->dim_m();
  if (max != other.dim_vectora()) {
    throw IncompatibleDimException(max, other.dim_vectora());
  }
  Vector c(nnz-1);
  int u = 0;
  for (int i = 0; i < m; i++) {
    c.elements[u] += elements_m[i] * other[index_st[i]];
    if (i < m - 1) {
      if (index_st[i] > index_st[i + 1]) {
        u++;
      }
    }
  }
  return c;
}

int CSRMatrix::dim_m() const {
  double max = -1000;
  for (int i = 0; i < m; i++) {
    if (index_st[i] >= max) {
      max = index_st[i];
    }
  }
  return (int) max + 1;
}

int CSRMatrix::dim_n() const {
  return nnz-1;
}

CSRMatrix operator*(const double a, CSRMatrix other) {
  return other*a;
}
