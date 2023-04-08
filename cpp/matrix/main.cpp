#include <iostream>
#include <complex>
#include <random>

#include "matrix.h"

template<typename T = int64_t>
using VecMatrix = std::vector<std::vector<T>>;
using Complex = std::complex<double>;

template<typename T>
T GenerateRandomElem(std::mt19937& gen) {
  std::uniform_int_distribution<T> distribution(std::numeric_limits<T>::min(),
                                                std::numeric_limits<T>::max());
  return distribution(gen);
}

template<>
Complex GenerateRandomElem(std::mt19937& gen) {;
  std::normal_distribution distribution;
  return {distribution(gen), distribution(gen)};
}

template<>
double GenerateRandomElem(std::mt19937& gen) {;
  std::normal_distribution distribution;
  return distribution(gen);
}


template<typename T>
VecMatrix<T> GenerateRandomMatrix(size_t rows_num, size_t columns_num) {
  std::mt19937 gen;
  VecMatrix<T> result(rows_num, std::vector<T>(columns_num));
  for (size_t i = 0; i < rows_num; ++i) {
    for (size_t j = 0; j < columns_num; ++j) {
      result[i][j] = GenerateRandomElem<T>(gen);
    }
  }
  return result;
}

template<typename T>
VecMatrix<T> GenerateRandomSymmetricMatrix(size_t size) {
  std::mt19937 gen;
  VecMatrix<T> result(size, std::vector<T>(size));
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = i; j < size; ++j) {
      result[i][j] = result[j][i] = GenerateRandomElem<T>(gen);
    }
  }
  return result;
}

int main() {
  VecMatrix<Complex> zero(7, std::vector<Complex>(3));
  VecMatrix<Complex> vector = GenerateRandomMatrix<Complex>(7, 3);
  Matrix<7, 3, Complex> matrix(vector);
  // std::cout << ();
  std::cout << (matrix + matrix * Complex(-1., 0.) == zero);
  return 0;
}
