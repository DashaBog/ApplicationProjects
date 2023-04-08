//  lego: 44000

#include <cassert>
#include <iostream>
#include <vector>

template <size_t N, size_t M, typename T = int64_t>
class Matrix {
  size_t rows_;
  size_t columns_;
  std::vector<std::vector<T>> data_;

 public:
  Matrix();
  ~Matrix() = default;
  std::vector<std::vector<T>> GetData() { return data_; }
  T& operator()(size_t i, size_t j);
  T operator()(size_t i, size_t j) const;
  Matrix(std::vector<std::vector<T>> vect);
  Matrix(T elem);
  Matrix<M, N, T> Transposed();
  T Trace();
  Matrix<N, M, T>& operator+=(const Matrix<N, M, T>& right);
  Matrix<N, M, T> operator+(const Matrix<N, M, T>& right);
  Matrix<N, M, T>& operator-=(const Matrix<N, M, T>& right);
  Matrix<N, M, T> operator-(const Matrix<N, M, T>& right);
  template <size_t K>
  Matrix<N, K, T> operator*(const Matrix<M, K, T>& left) const;
  Matrix<N, M, T> operator*(T elem);
  bool operator==(const Matrix& right);

 private:
  void CheckIndexes(size_t i, size_t j) const;
};

template <size_t N, size_t M, typename T>
void Matrix<N, M, T>::CheckIndexes(size_t i, size_t j) const {
  assert(i < rows_);
  assert(j < columns_);
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix() : rows_(N), columns_(M) {
  data_.assign(N, std::vector<T>(M, T()));
}

template <size_t N, size_t M, typename T>
T& Matrix<N, M, T>::operator()(size_t i, size_t j) {
  CheckIndexes(i, j);
  return data_[i][j];
}

template <size_t N, size_t M, typename T>
T Matrix<N, M, T>::operator()(size_t i, size_t j) const {
  CheckIndexes(i, j);
  return data_[i][j];
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(std::vector<std::vector<T>> vect)
    : rows_(N), columns_(M) {
  data_.assign(N, std::vector<T>(M, T()));
  for (size_t i = 0; i < rows_; ++i) {
    for (size_t j = 0; j < columns_; ++j) {
      data_[i][j] = vect[i][j];
    }
  }
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(T elem) : rows_(N), columns_(M) {
  data_.assign(N, std::vector<T>(M, T()));
  for (size_t i = 0; i < rows_; ++i) {
    for (size_t j = 0; j < columns_; ++j) {
      data_[i][j] = elem;
    }
  }
}

template <size_t N, size_t M, typename T>
Matrix<M, N, T> Matrix<N, M, T>::Transposed() {
  Matrix<M, N, T> result;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      result(j, i) = (*this)(i, j);
    }
  }
  return result;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator+=(const Matrix<N, M, T>& right) {
  assert(rows_ == right.rows_ && columns_ == right.columns_);
  for (size_t i = 0; i < right.rows_; i++) {
    for (size_t j = 0; j < right.columns_; j++) {
      operator()(i, j) += right(i, j);
    }
  }
  return *this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> Matrix<N, M, T>::operator+(const Matrix<N, M, T>& right) {
  assert(rows_ == right.rows_ && columns_ == right.columns_);
  Matrix<N, M, T> result;
  for (size_t i = 0; i < right.rows_; i++) {
    for (size_t j = 0; j < right.columns_; j++) {
      result(i, j) = operator()(i, j) + right(i, j);
    }
  }
  return result;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator-=(const Matrix<N, M, T>& right) {
  assert(rows_ == right.rows_ && columns_ == right.columns_);
  for (size_t i = 0; i < right.rows_; i++) {
    for (size_t j = 0; j < right.columns_; j++) {
      operator()(i, j) -= right(i, j);
    }
  }
  return *this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> Matrix<N, M, T>::operator-(const Matrix<N, M, T>& right) {
  assert(rows_ == right.rows_ && columns_ == right.columns_);
  Matrix<N, M, T> result;
  for (size_t i = 0; i < right.rows_; i++) {
    for (size_t j = 0; j < right.columns_; j++) {
      result(i, j) = operator()(i, j) - right(i, j);
    }
  }
  return result;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> Matrix<N, M, T>::operator*(T elem) {
  Matrix<N, M, T> result;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      result(i, j) = elem * (*this)(i, j);
    }
  }
  return result;
}

template <size_t N, size_t M, typename T>
template <size_t K>
Matrix<N, K, T> Matrix<N, M, T>::operator*(const Matrix<M, K, T>& left) const {
  Matrix<N, K, T> result;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < K; ++j) {
      for (size_t k = 0; k < M; ++k) {
        result(i, j) += (*this)(i, k) * left(k, j);
      }
    }
  }
  return result;
}

template <size_t N, size_t M, typename T>
T Matrix<N, M, T>::Trace() {
  assert(N == M);
  T result = 0;
  for (size_t i = 0; i < N; ++i) {
    result += operator()(i, i);
  }
  return result;
}

template <size_t N, size_t M, typename T>
bool Matrix<N, M, T>::operator==(const Matrix& right) {
  if (rows_ != right.rows_ || columns_ != right.columns_) {
    return false;
  }
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      if (operator()(i, j) != right(i, j)) {
        return false;
      }
    }
  }
  return true;
}