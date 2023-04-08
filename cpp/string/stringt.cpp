#include "stringt.h"

#include <cstdlib>
#include <cstring>
#include <iostream>

String::String(size_t size, char character) {
  str_length_ = size;
  str_capacity_ = size;
  str_ = static_cast<char*>(realloc(str_, (size + 1) * sizeof(char)));
  for (size_t i = 0; i < str_length_; i++) {
    str_[i] = character;
  }
  str_[str_length_] = '\0';
}

String::String(const char* str) {
  size_t size = strlen(str);
  str_ = static_cast<char*>(realloc(str_, (size + 1) * sizeof(char)));
  str_capacity_ = size;
  str_length_ = size;
  for (size_t i = 0; i < size; i++) {
    str_[i] = str[i];
  }
  str_[str_length_] = '\0';
}

String::String(const String& str) {
  str_ =
      static_cast<char*>(realloc(str_, (str.str_capacity_ + 1) * sizeof(char)));
  for (size_t j = 0; j < str.str_length_; j++) {
    str_[j] = str.str_[j];
  }
  str_length_ = str.str_length_;
  str_[str_length_] = '\0';
  str_capacity_ = str.str_capacity_;
}

String::~String() {
  free(str_);
  str_length_ = 0;
  str_capacity_ = 0;
}

void String::Clear() { str_length_ = 0; }

void String::PushBack(char character) {
  if (str_length_ == str_capacity_) {
    Reserve(str_capacity_ * increase_);
  }
  str_[str_length_] = character;
  str_[str_length_ + 1] = '\0';
  str_length_ += 1;
}

void String::PopBack() {
  if (str_length_ == 0) {
    return;
  }
  str_[str_length_ - 1] = '\0';
  str_length_ -= 1;
}

void String::Resize(size_t new_size) {
  if (str_length_ == new_size) {
    return;
  }
  if (new_size < str_length_) {
    str_[new_size] = '\0';
    str_length_ = new_size;

    return;
  }
  if (new_size >= str_capacity_) {
    str_ = static_cast<char*>(realloc(str_, (new_size + 1) * sizeof(char)));
    str_capacity_ = new_size;
  }
  str_[str_length_] = '0';
  str_length_ = new_size;
  str_[str_length_] = '\0';
}

void String::Resize(size_t new_size, char character) {
  if (str_length_ == new_size) {
    return;
  }
  if (new_size < str_length_) {
    str_[new_size] = '\0';
    str_length_ = new_size;
    return;
  }
  if (new_size > str_capacity_) {
    str_ = static_cast<char*>(realloc(str_, (new_size + 1) * sizeof(char)));
    str_capacity_ = new_size;
  }
  for (size_t i = str_length_; i < new_size; i++) {
    str_[i] = character;
  }
  str_length_ = new_size;
  str_[str_length_] = '\0';
}

void String::Reserve(size_t new_cap) {
  if (str_capacity_ == 0 && new_cap == 0) {
    new_cap = 1;
  }
  if (str_capacity_ >= new_cap) {
    return;
  }
  str_capacity_ = new_cap;
  str_ = static_cast<char*>(realloc(str_, (str_capacity_ + 1) * sizeof(char)));
}

void String::ShrinkToFit() {
  if (str_length_ == str_capacity_) {
    return;
  }
  str_ = static_cast<char*>(realloc(str_, (str_length_ + 1) * sizeof(char)));
  str_capacity_ = str_length_;
}

void String::Swap(String& other) {
  std::swap(str_, other.str_);
  std::swap(str_length_, other.str_length_);
  std::swap(str_capacity_, other.str_capacity_);
}

const char& String::operator[](size_t i) const { return *(str_ + i); }

char& String::operator[](size_t i) { return *(str_ + i); }

const char& String::Front() const { return str_[0]; }

char& String::Front() { return str_[0]; }

const char& String::Back() const { return str_[str_length_ - 1]; }

char& String::Back() { return str_[str_length_ - 1]; }

bool String::Empty() const { return (str_length_ == 0); }

size_t String::Size() const { return str_length_; }

size_t String::Capacity() const { return str_capacity_; }

const char* String::Data() const { return str_; }

char* String::Data() { return &str_[0]; }

bool operator==(const String& lhs, const String& rhs) {
  return lhs.Compare(rhs) == 0;
}

bool operator!=(const String& lhs, const String& rhs) {
  return lhs.Compare(rhs) != 0;
}

bool operator<(const String& lhs, const String& rhs) {
  return lhs.Compare(rhs) < 0;
}

bool operator>(const String& lhs, const String& rhs) {
  return lhs.Compare(rhs) > 0;
}

bool operator<=(const String& lhs, const String& rhs) {
  return lhs.Compare(rhs) <= 0;
}

bool operator>=(const String& lhs, const String& rhs) {
  return lhs.Compare(rhs) >= 0;
}

String& String::operator+=(const String& s) {
  Reserve(str_length_ + s.str_length_);

  std::memcpy((str_ + str_length_), s.str_, s.str_length_);
  str_[str_length_ + s.str_length_] = '\0';
  str_length_ += s.str_length_;
  return *this;
}

String& String::operator=(const String& other) {
  if (this != &other) {
    Reserve(other.str_capacity_ + 1);
    for (size_t j = 0; j < other.str_length_; j++) {
      str_[j] = other.str_[j];
    }
    str_length_ = other.str_length_;
    str_capacity_ = other.str_capacity_;
    str_[str_length_] = '\0';
  }
  return *this;
}

String operator+(const String& lhs, const String& rhs) {
  String to_return = lhs;
  to_return += rhs;
  return to_return;
}

String& String::operator*=(const size_t kNum) {
  Reserve(str_length_ * kNum + 1);
  for (size_t i = 0; i < kNum; i++) {
    std::memcpy((str_ + str_length_ * i), str_, str_length_);
  }
  str_[str_length_ * kNum] = '\0';
  str_length_ *= kNum;
  return *this;
}

String operator*(const String& rhs, size_t k_num) {
  if (k_num == 0) {
    String to_return = "";
    return to_return;
  }
  String to_return = rhs;
  for (size_t i = 0; i < k_num - 1; i++) {
    to_return += rhs;
  }
  return to_return;
}

std::ostream& operator<<(std::ostream& out, const String& s) {
  if (s.Size() > 0) {
    for (size_t i = 0; i < s.Size(); i++) {
      out << s[i];
    }
  } else {
    out << "";
  }
  return out;
}

std::istream& operator>>(std::istream& in, String& s) {
  std::string tmp;
  char c;
  s.Clear();
  in >> c;
  while (!in.eof()) {
    s.PushBack(c);
    in >> c;
  }
  return in;
}

int String::Compare(const String& rhs) const {
  if (str_length_ < rhs.str_length_) {
    return -1;
  }
  if (str_length_ > rhs.str_length_) {
    return 1;
  }

  size_t k_num = 0;
  while ((k_num < str_length_) && (str_[k_num] == rhs[k_num])) {
    k_num++;
  }
  if (k_num == str_length_) {
    return 0;
  }
  if ((isalpha(str_[k_num]) != 0) && (isalpha(rhs.str_[k_num]) != 0)) {
    if (str_[k_num] < rhs.str_[k_num]) {
      return -1;
    }
    return 1;
  }
  return 0;
}

std::vector<String> String::Split(const String& delim) {
  if (str_length_ == 0) {
    std::vector<String> res;
    res.emplace_back("");
    return res;
  }
  std::vector<String> res;
  String buffer;
  size_t num = 0;
  for (size_t i = 0; i < str_length_; i++) {
    buffer.PushBack(str_[i]);
    if (str_[i] == delim[num]) {
      num++;
    } else {
      num = 0;
    }
    if (num == delim.Size()) {
      for (size_t j = 0; j < delim.Size(); j++) {
        buffer.PopBack();
      }
      res.push_back(buffer);
      num = 0;
      buffer.Clear();
    }
  }
  res.push_back(buffer);
  return res;
}

String String::Join(const std::vector<String>& strings) const {
  String res;
  if (strings.empty()) {
    return res;
  }
  if (strings[0] == "") {
    res = "";
    return res;
  }
  for (size_t i = 0; i < strings.size() - 1; i++) {
    res += (strings[i] + (*this));
  }
  res += strings[strings.size() - 1];

  return res;
}