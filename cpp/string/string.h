#pragma once

#include <iostream>
#include <vector>

class String {
 private:
  char* str_ = nullptr;
  size_t str_length_ = 0;
  size_t str_capacity_ = 0;
  const size_t kIncrease = 2;

 public:
  String() = default;
  String(size_t, char);
  String(const char*);
  String(const String&);
  String& operator=(String&);
  ~String();
  void Clear();
  void PushBack(char);
  void PopBack();
  void Resize(size_t);
  void Resize(size_t, char);
  void Reserve(size_t new_cap);
  void ShrinkToFit();
  void Swap(String&);
  char& operator[](size_t);
  const char& operator[](size_t) const;
  char& Front();
  const char& Front() const;
  char& Back();
  const char& Back() const;
  bool Empty() const;
  size_t Size() const;
  size_t Capacity() const;
  const char* Data() const;
  String& operator=(const String& other);
  friend bool operator<(const String&, const String&);
  friend bool operator>(const String&, const String&);
  friend bool operator>=(const String&, const String&);
  friend bool operator<=(const String&, const String&);
  friend bool operator==(const String&, const String&);
  friend bool operator!=(const String&, const String&);
  String& operator*=(size_t);
  String& operator+=(const String&);
  friend String operator+(const String&, const String&);
  friend std::ostream& operator<<(std::ostream&, String&);
  friend std::istream& operator>>(std::istream&, String&);
  std::vector<String> Split(const String& delim = " ");
  String Join(const std::vector<String>& strings) const;
};


//
#include "stringt.h"

#include <cstring>

String::String(size_t size, char character) {
  str_capacity_ = size;
  str_length_ = size;
  str_ = (char*)realloc(str_, sizeof(char) * (size + 1));
  for (size_t i = 0; i < size; i++) {
    str_[i] = character;
  }
  str_[str_length_] = '\0';
}

String::String(const char* str) {
  size_t size = strlen(str);
  str_capacity_ = size;
  str_length_ = size;
  str_ = (char*)realloc(str_, sizeof(char) * (size + 1));
  for (size_t i = 0; i < size; i++) {
    str_[i] = str[i];
  }
  str_[str_length_] = '\0';
}

String::String(const String& str) {
  str_capacity_ = str.str_capacity_;
  str_length_ = str.str_length_;
  str_ = (char*)realloc(str_, sizeof(char) * (str_capacity_ + 1));
  for (size_t i = 0; i < str_length_; i++) {
    str_[i] = str[i];
  }
  str_[str_length_] = '\0';
}

String& String::operator=(String& str) {
  str_capacity_ = str.str_capacity_;
  str_length_ = str.str_length_;
  str_ = (char*)realloc(str_, sizeof(char) * (str_capacity_ + 1));
  for (size_t i = 0; i < str_length_; i++) {
    str_[i] = str[i];
  }
  str_[str_length_] = '\0';
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

String::~String() {
  free(str_);
  str_capacity_ = 0;
  str_length_ = 0;
}

void String::Clear() { str_length_ = 0; }

void String::PushBack(char character) {
  if (str_length_ >= str_capacity_) {
    str_capacity_ = str_capacity_ * kIncrease;
    str_ = (char*)realloc(str_, sizeof(char) * (str_capacity_ + 1));
  }
  str_[str_length_] = character;
  str_[str_length_ + 1] = '\0';
  str_length_ += 1;
}

void String::PopBack() {
  if (str_length_ == 0) {
    return;
  }
  str_[str_length_] = '\0';
  str_length_ -= 1;
}

void String::Resize(size_t new_size) {  // !
  if (str_length_ == new_size) {
    return;
  }
  if (new_size < str_length_) {
    str_[new_size] = '\0';
    str_length_ = new_size;
    return;
  }
  if (new_size >= str_capacity_) {
    str_ = (char*)realloc(str_, (new_size + 1) * sizeof(char));
    str_capacity_ = new_size;
  }
  str_[str_length_] = '0';
  str_length_ = new_size;
  str_[str_length_] = '\0';
}

void String::Resize(size_t new_size, char character) {  // !
  if (str_length_ == new_size) {
    return;
  }
  if (new_size < str_length_) {
    str_[new_size] = '\0';
    str_length_ = new_size;
    return;
  }
  if (new_size > str_capacity_) {
    str_ = (char*)realloc(str_, (new_size + 1) * sizeof(char));
    str_capacity_ = new_size;
  }
  for (size_t i = str_length_; i < new_size; i++) {
    str_[i] = character;
  }
  str_length_ = new_size;
  str_[str_length_] = '\0';
}

void String::Reserve(size_t new_cap) {
  if (str_capacity_ <= new_cap) {
    return;
  }
  str_capacity_ = new_cap;
  str_ = (char*)realloc(str_, (str_capacity_ + 1) * sizeof(char));
}

void String::ShrinkToFit() {
  if (str_capacity_ > str_length_) {
    str_ = (char*)realloc(str_, (str_length_ + 1) * sizeof(char));
    str_capacity_ = str_length_;
  }
}

void String::Swap(String& str) {
  std::swap(str_, str.str_);
  std::swap(str_length_, str.str_length_);
  std::swap(str_capacity_, str.str_capacity_);
}

char& String::operator[](const size_t kI) { return str_[kI]; }

const char& String::operator[](const size_t kI) const { return str_[kI]; }

char& String::Front() { return str_[0]; }

const char& String::Front() const { return str_[0]; }

char& String::Back() { return str_[str_length_ - 1]; }

const char& String::Back() const { return str_[str_length_ - 1]; }

bool String::Empty() const { return (str_length_ == 0); }

size_t String::Size() const { return str_length_; }

size_t String::Capacity() const { return str_capacity_; }

const char* String::Data() const { return str_; }

bool operator<(const String& str_first, const String& str_second) {
  if (str_first.str_length_ < str_second.str_length_) {
    return true;
  }
  if (str_first.str_length_ > str_second.str_length_) {
    return false;
  }
  size_t k_num = 0;
  while ((k_num < str_first.str_length_) &&
      (str_first[k_num] == str_second[k_num])) {
    k_num++;
  }
  if (k_num == str_first.str_length_) {
    return false;
  }
  return str_first[k_num] < str_second[k_num];
}

bool operator>(const String& str_first, const String& str_second) {
  if (str_first.str_length_ > str_second.str_length_) {
    return true;
  }
  if (str_first.str_length_ < str_second.str_length_) {
    return false;
  }
  size_t k_num = 0;
  while ((k_num < str_first.str_length_) &&
      (str_first[k_num] == str_second[k_num])) {
    k_num++;
  }
  if (k_num == str_first.str_length_) {
    return false;
  }
  return str_first[k_num] > str_second[k_num];
}

bool operator>=(const String& str_first, const String& str_second) {
  return !(str_first < str_second);
}

bool operator<=(const String& str_first, const String& str_second) {
  return !(str_first > str_second);
}

bool operator==(const String& str_first, const String& str_second) {
  return !(str_first < str_second || str_first > str_second);
}

bool operator!=(const String& str_first, const String& str_second) {
  return !(str_first == str_second);
}

String& String::operator+=(const String& s) {
  Reserve(str_length_ + s.str_length_);

  std::memcpy((str_ + str_length_), s.str_, s.str_length_);
  str_[str_length_ + s.str_length_] = '\0';
  str_length_ += s.str_length_;
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

std::ostream& operator<<(std::ostream& out, String& s) {
  if (s.Size() > 0) {
    for (size_t i = 0; i < s.Size(); i++) {
      out << s[i];
    }
  }
  return out;
}

std::istream& operator>>(std::istream& in, String& s) {
  char c;
  s.Clear();
  in >> c;
  while (!in.eof()) {
    s.PushBack(c);
    in >> c;
  }
  return in;
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