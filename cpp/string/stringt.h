#pragma once

#include <iostream>
#include <vector>

class String {
  const size_t kIncrease = 2;

 private:
  char* str_ = nullptr;
  size_t str_length_ = 0;
  size_t str_capacity_ = 0;

  size_t increase_ = kIncrease;

 public:
  String() = default;

  String(const char* str);

  String(size_t size, char character);

  String(const String& str);

  ~String();

  void Clear();

  void PushBack(char character);

  void PopBack();

  void Resize(size_t new_size);

  void Resize(size_t new_size, char character);

  void Reserve(size_t new_cap);

  void ShrinkToFit();

  void Swap(String& other);

  char& operator[](size_t);

  const char& operator[](size_t) const;

  const char& Front() const;

  char& Front();

  const char& Back() const;

  char& Back();

  friend bool operator==(const String&, const String&);

  friend bool operator!=(const String&, const String&);

  friend bool operator<(const String&, const String&);

  friend bool operator>(const String&, const String&);

  friend bool operator<=(const String&, const String&);

  friend bool operator>=(const String&, const String&);

  String& operator+=(const String&);

  friend String operator+(const String& lhs, const String& rhs);

  String& operator=(const String& other);

  String& operator*=(size_t num);

  friend std::ostream& operator<<(std::ostream& out, const String& s);

  friend std::istream& operator>>(std::istream& in, String& s);

  friend String operator*(const String&, size_t k_num);

  bool Empty() const;

  size_t Size() const;

  size_t Capacity() const;

  const char* Data() const;

  char* Data();

  std::vector<String> Split(const String& delim = " ");

  String Join(const std::vector<String>& strings) const;

 private:
  int Compare(const String& rhs) const;
};