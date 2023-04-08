#pragma once
#include <iomanip>
#include <iostream>
#include <vector>

class BigInt {
  static const int kBase = 1000000000;
  static const int kPres = 9;
  std::vector<int> digits_;
  bool is_negative_ = false;

  void RemoveZeros();
  void ShiftDigits();
  friend int BinSearch(BigInt&, BigInt&);

 public:
  BigInt() = default;
  BigInt(std::string);
  BigInt(int64_t);

  friend std::ostream& operator<<(std::ostream&, const BigInt&);
  friend std::istream& operator>>(std::istream&, BigInt&);
  operator std::string() const;
  BigInt operator-() const;
  BigInt operator++();
  BigInt operator++(int);
  BigInt operator--();
  BigInt operator--(int);
  friend bool operator==(const BigInt&, const BigInt&);
  friend bool operator<(const BigInt&, const BigInt&);
  friend bool operator!=(const BigInt&, const BigInt&);
  friend bool operator<=(const BigInt&, const BigInt&);
  friend bool operator>(const BigInt&, const BigInt&);
  friend bool operator>=(const BigInt&, const BigInt&);
  friend BigInt operator+(BigInt, const BigInt&);
  friend BigInt operator-(BigInt, const BigInt&);
  friend BigInt operator*(const BigInt&, const BigInt&);
  friend BigInt operator/(const BigInt&, const BigInt&);
  friend BigInt operator%(const BigInt&, const BigInt&);
};