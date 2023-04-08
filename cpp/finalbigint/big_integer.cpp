#include "big_integer.h"

BigInt::BigInt(std::string str) {
  if (str.length() == 0) {
    is_negative_ = false;
  } else {
    if (str[0] == '-') {
      str.erase(0, 1);
      is_negative_ = true;
    } else {
      is_negative_ = false;
    }
    for (int64_t i = str.length(); i > 0; i -= kPres) {
      if (i < kPres) {
        digits_.push_back(atoi(str.substr(0, i).c_str()));
      } else {
        digits_.push_back(atoi(str.substr(i - kPres, kPres).c_str()));
      }
    }
    RemoveZeros();
  }
}

void BigInt::RemoveZeros() {
  while (digits_.size() > 1 && digits_.back() == 0) {
    digits_.pop_back();
  }
  if (digits_.size() == 1 && digits_[0] == 0) {
    is_negative_ = false;
  }
}

std::ostream& operator<<(std::ostream& out, const BigInt& bi) {
  if (bi.is_negative_ && !bi.digits_.empty()) {
    out << '-';
  }
  if (bi.digits_.empty()) {
    out << '0' << "\n";
  } else {
    // printf("%d", bi.digits_.back());
    out << bi.digits_.back();
  }
  for (int64_t i = bi.digits_.size() - 2; i >= 0; --i) {
    // printf("%09d", bi.digits_[i]);
    char old_fill = out.fill('0');
    out << std::setw(BigInt::kPres) << bi.digits_[i];
    out.fill(old_fill);
  }
  return out;
}

std::istream& operator>>(std::istream& in, BigInt& bi) {
  std::string input;
  in >> input;
  if (input[0] >= '0' && input[0] <= '9' || input[0] == '-') {
    bi = input;
  }
  return in;
}

bool operator==(const BigInt& left, const BigInt& right) {
  if (left.is_negative_ != right.is_negative_ && !left.digits_.empty()) {
    return false;
  }
  if (left.digits_.empty()) {
    return right.digits_.empty() ||
           (right.digits_.size() == 1 && right.digits_[0] == 0);
  }
  if (right.digits_.empty()) {
    return left.digits_.size() == 1 && left.digits_[0] == 0;
  }
  if (left.digits_.size() == right.digits_.size()) {
    for (uint32_t i = 0; i < left.digits_.size(); ++i) {
      if (left.digits_[i] != right.digits_[i]) {
        return false;
      }
    }
    return true;
  }
  return false;
}

BigInt BigInt::operator-() const {
  BigInt copy(*this);
  copy.is_negative_ = !copy.is_negative_;
  return copy;
}

bool operator<(const BigInt& left, const BigInt& right) {
  if (left == right) {
    return false;
  }
  if (left.is_negative_) {
    if (right.is_negative_) {
      return ((-right) < (-left));
    }
    return true;
  }
  if (!right.is_negative_) {
    if (left.digits_.size() != right.digits_.size()) {
      return left.digits_.size() < right.digits_.size();
    }
    for (uint32_t i = left.digits_.size() - 1;; --i) {
      if (left.digits_[i] != right.digits_[i]) {
        return left.digits_[i] < right.digits_[i];
      }
    }
  }
  return false;
}

bool operator!=(const BigInt& left, const BigInt& right) {
  return !(left == right);
}

bool operator<=(const BigInt& left, const BigInt& right) {
  return (left < right || left == right);
}

bool operator>(const BigInt& left, const BigInt& right) {
  return !(left < right && left == right);
}

bool operator>=(const BigInt& left, const BigInt& right) {
  return (left > right || left == right);
}

BigInt operator+(BigInt left, const BigInt& right) {
  if (left.is_negative_) {
    if (right.is_negative_) {
      return -(-left + (-right));
    }
    return right - (-left);
  }
  if (right.is_negative_) {
    return left - (-right);
  }
  int carryflag = 0;
  for (uint32_t i = 0;
       i < std::max(left.digits_.size(), right.digits_.size()) ||
       carryflag != 0;
       ++i) {
    if (i == left.digits_.size()) {
      left.digits_.push_back(0);
    }
    if (i < right.digits_.size()) {
      left.digits_[i] += carryflag + right.digits_[i];
    } else {
      left.digits_[i] += carryflag;
    }
    carryflag = static_cast<int>(left.digits_[i] >= BigInt::kBase);
    if (carryflag != 0) {
      left.digits_[i] -= BigInt::kBase;
    }
  }
  return left;
}

BigInt BigInt::operator++() {
  BigInt inc(1);
  return *this = (*this + inc);
}

BigInt::operator std::string() const {
  std::stringstream ss;
  ss << *this;
  return ss.str();
}

BigInt::BigInt(int64_t number) {
  is_negative_ = static_cast<bool>(number < 0);
  while (number != 0) {
    digits_.push_back(std::abs(number % kBase));
    number /= kBase;
  }
}

BigInt BigInt::operator++(int) {
  BigInt inc(1);
  *this = (*this + inc);
  return *this - inc;
}

BigInt BigInt::operator--() {
  BigInt inc(1);
  return *this = (*this - inc);
}

BigInt BigInt::operator--(int) {
  BigInt inc(1);
  *this = (*this - inc);
  return *this + inc;
}

BigInt operator-(BigInt left, const BigInt& right) {
  if (right.is_negative_) {
    return left + (-right);
  }
  if (left.is_negative_) {
    return -(-left + right);
  }
  if (left < right) {
    return -(right - left);
  }
  int carry = 0;
  for (uint32_t i = 0; i < right.digits_.size() || carry != 0; ++i) {
    if (i < right.digits_.size()) {
      left.digits_[i] -= carry + right.digits_[i];
    } else {
      left.digits_[i] -= carry;
    }
    carry = static_cast<int>(left.digits_[i] < 0);
    if (carry != 0) {
      left.digits_[i] += BigInt::kBase;
    }
  }
  left.RemoveZeros();
  return left;
}

BigInt operator*(const BigInt& left, const BigInt& right) {
  BigInt result;
  result.digits_.resize(left.digits_.size() + right.digits_.size());
  for (uint32_t i = 0; i < left.digits_.size(); ++i) {
    int carry = 0;
    for (uint32_t j = 0; j < right.digits_.size() || carry != 0; ++j) {
      long long cur;
      if (j < right.digits_.size()) {
        cur = result.digits_[i + j] +
              left.digits_[i] * static_cast<long long>(right.digits_[j]) +
              carry;
      } else {
        cur = result.digits_[i + j] + carry;
      }
      result.digits_[i + j] = static_cast<int>(cur % BigInt::kBase);
      carry = static_cast<int>(cur / BigInt::kBase);
    }
  }
  result.is_negative_ = (left.is_negative_ != right.is_negative_);
  result.RemoveZeros();
  return result;
}

void BigInt::ShiftDigits() {
  if (digits_.empty()) {
    digits_.push_back(0);
    return;
  }
  digits_.push_back(digits_[digits_.size() - 1]);
  for (unsigned long i = digits_.size() - 2; i > 0; --i) {
    digits_[i] = digits_[i - 1];
  }
  digits_[0] = 0;
}

int BinSearch(BigInt& pointer, BigInt& current) {
  int pos = 0;
  int left = 0;
  int right = BigInt::kBase;
  while (left <= right) {
    int mid = (left + right) / 2;
    BigInt tested = pointer * mid;
    if (tested <= current) {
      pos = mid;
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return pos;
}

BigInt operator/(const BigInt& left, const BigInt& right) {
  BigInt pointer = right;
  pointer.is_negative_ = false;
  BigInt result;
  BigInt current;
  result.digits_.resize(left.digits_.size());
  for (long long i = (long long)(left.digits_.size()) - 1; i >= 0; --i) {
    current.ShiftDigits();
    current.digits_[0] = left.digits_[i];
    current.RemoveZeros();
    result.digits_[i] = BinSearch(pointer, current);
    current = current - pointer * result.digits_[i];
  }
  result.is_negative_ = (left.is_negative_ != right.is_negative_);
  result.RemoveZeros();
  return result;
}

BigInt operator%(const BigInt& left, const BigInt& right) {
  BigInt result = left - (left / right) * right;
  // if (result._is_negative) result += right;
  return result;
}