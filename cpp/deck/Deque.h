#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using std::vector;

template <typename T>
class Deque {
 public:
  Deque();
  Deque(const Deque& deque);
  Deque(size_t count);
  Deque(size_t count, const T& value);
  ~Deque();
  Deque& operator=(const Deque& other);
  size_t size() const;
  bool empty();
  T& operator[](size_t index);
  const T& operator[](size_t index) const;
  T& at(size_t index);
  const T& at(size_t index) const;
  void push_back(const T& value);
  void pop_back();
  void push_front(const T& value);
  void pop_front();

  template <bool IsConst = false>
  struct Iterator {
    size_t arrnum;
    size_t indexnum;
    std::conditional_t<IsConst, const Deque<T>*, Deque<T>*> deq;

    const size_t kCapacityPointer = 64;

    Iterator() = default;

    ~Iterator() = default;

    Iterator(size_t arrnum, size_t indexnum,
             std::conditional_t<IsConst, const Deque<T>*, Deque<T>*> deq)
        : arrnum(arrnum), indexnum(indexnum), deq(deq) {}

    Iterator(const Iterator& iter) {
      if (this == &iter) {
        return;
      }
      indexnum = iter.indexnum;
      arrnum = iter.arrnum;
      deq = iter.deq;
    }

    Iterator& operator=(const Iterator& iter) {
      if (this == &iter) {
        return *this;
      }
      indexnum = iter.indexnum;
      arrnum = iter.arrnum;
      deq = iter.deq;
      return *this;
    }

    Iterator operator-(int value) const {
      int diffarr = (indexnum - value) / kCapacityPointer;
      int newindex = (indexnum - value) % kCapacityPointer;
      if (newindex < 0) {
        diffarr -= 1;
        newindex += kCapacityPointer;
      }
      return Iterator(arrnum + diffarr, newindex, this->deq);
    }

    Iterator operator+(int value) const { return *this - (-value); }

    Iterator operator+=(int value) {
      *this = *this + value;
      return *this;
    }

    Iterator& operator--() {
      *this = *this - 1;
      return *this;
    }

    Iterator operator--(int) {
      Iterator res = *this;
      *this = *this - 1;
      return res;
    }

    Iterator& operator++() {
      *this = *this - (-1);
      return *this;
    }

    Iterator operator++(int) {
      Iterator res = *this;
      *this = *this - (-1);
      return res;
    }

    std::conditional_t<IsConst, const T&, T&> operator*() const {
      return deq->deque[arrnum][indexnum];
    }

    std::conditional_t<IsConst, const T*, T*> operator->() const {
      return &deq->deque[arrnum][indexnum];
    }

    bool operator==(const Iterator& iter) const {
      return (this->arrnum == iter.arrnum && this->indexnum == iter.indexnum);
    }

    bool operator<(const Iterator& iter) const {
      return (arrnum == iter.arrnum && indexnum < iter.indexnum) ||
          (arrnum < iter.arrnum);
    }

    bool operator!=(const Iterator& iter) const { return !(*this == iter); }

    bool operator>=(const Iterator& iter) const { return !(*this < iter); }

    bool operator<=(const Iterator& iter) const {
      return (*this == iter) || (*this < iter);
    }

    bool operator>(const Iterator& iter) const { return !(*this <= iter); }

    size_t operator-(const Iterator& iter) const {
      return (arrnum - iter.arrnum - 1) * kCapacityPointer + (indexnum + 1) +
          (kCapacityPointer - 1 - iter.indexnum);
    }

    using value_type = typename std::conditional<IsConst, const T, T>::type;
    using pointer = typename std::conditional<IsConst, const T*, T*>::type;
    using iterator_category = typename std::random_access_iterator_tag;
    using reference = typename std::conditional<IsConst, const T&, T&>::type;
    using difference_type = typename std::ptrdiff_t;
  };

  using iterator = Iterator<false>;
  using const_iterator = Iterator<true>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  iterator begin() { return iterator(first_arr, front, this); }

  const_iterator cbegin() const {
    return const_iterator(first_arr, front, this);
  }

  iterator end() {
    auto copy = iterator(last_arr, back, this);
    copy++;
    return copy;
  }

  const_iterator cend() const {
    auto copy = const_iterator(last_arr, back, this);
    copy++;
    return copy;
  }

  reverse_iterator rbegin() { return std::reverse_iterator(end()); }

  reverse_iterator rend() { return std::reverse_iterator(begin()); }

  const_reverse_iterator rbegin() const {
    return std::reverse_iterator(cend());
  }

  const_reverse_iterator rend() const {
    return std::reverse_iterator(cbegin());
  }

  const_reverse_iterator crbegin() const {
    return std::reverse_iterator(cend());
  }

  const_reverse_iterator crend() const {
    return std::reverse_iterator(cbegin());
  }

  void insert(const iterator& iter, const T& value) {
    push_back(value);
    for (auto i = --end(); i != iter; i--) {
      std::iter_swap(i, i - 1);
    }
  }

  void erase(const iterator& iter) {
    for (auto i = iter; i != --end(); i++) {
      std::iter_swap(i, i + 1);
    }
    pop_back();
  }

  vector<T*> deque;
  size_t first_arr = 0;
  size_t last_arr = 0;
  size_t front = 0;
  size_t back = 0;
  size_t sizedeque = 0;

 private:
  static const size_t kCapacity = 64;
};

template <typename T>
Deque<T>::Deque() {
  deque.resize(1);
  deque[0] = reinterpret_cast<T*>(new int8_t[sizeof(T) * kCapacity]);
}

template <typename T>
Deque<T>::~Deque() {
  for (size_t i = first_arr; i <= last_arr; ++i) {
    delete[](deque[i]);
  }
}

template <typename T>
Deque<T>::Deque(const Deque& dequet)
    : first_arr(dequet.first_arr),
      last_arr(dequet.last_arr),
      front(dequet.front),
      back(dequet.back),
      sizedeque(dequet.sizedeque) {
  this->deque.resize(dequet.size());
  for (size_t i = first_arr; i <= last_arr; ++i) {
    this->deque[i] = reinterpret_cast<T*>(new int8_t[kCapacity * sizeof(T)]);
    for (size_t j = 0; j < kCapacity; ++j) {
      if (i == first_arr && j < front) {
        continue;
      }
      if (i == last_arr && j > back) {
        break;
      }
      new (this->deque[i] + j) T(dequet.deque[i][j]);
    }
  }
}

template <typename T>
Deque<T>::Deque(size_t count)
    : first_arr(0),
      last_arr(std::max((count + kCapacity - 1) / kCapacity, size_t(1) - 1)),
      front(0),
      back((count + kCapacity - 1) % kCapacity),
      sizedeque(count) {
  deque.resize(count);
  for (size_t i = first_arr; i <= last_arr; ++i) {
    deque[i] = reinterpret_cast<T*>(new int8_t[kCapacity * sizeof(T)]);
    for (size_t j = 0; j < kCapacity; ++j) {
      if (j == last_arr && j > back) {
        break;
      }
      new (deque[i] + j) T();
    }
  }
}

template <typename T>
Deque<T>::Deque(size_t count, const T& value)
    : first_arr(0),
      last_arr(std::max(((count + kCapacity - 1) / kCapacity) - 1, size_t(0))),
      front(0),
      back((count + kCapacity - 1) % kCapacity),
      sizedeque(count) {
  deque.resize(last_arr + 1);
  for (size_t i = first_arr; i <= last_arr; ++i) {
    deque[i] = reinterpret_cast<T*>(new int8_t[kCapacity * sizeof(T)]);
    for (size_t j = 0; j < kCapacity; ++j) {
      if (i == last_arr && j > back) {
        break;
      }
      new (deque[i] + j) T(value);
    }
  }
}

template <typename T>
Deque<T>& Deque<T>::operator=(const Deque& other) {
  Deque copy = Deque(other);
  std::swap(copy.sizedeque, sizedeque);
  std::swap(copy.deque, deque);
  std::swap(copy.first_arr, first_arr);
  std::swap(copy.last_arr, last_arr);
  std::swap(copy.front, front);
  std::swap(copy.back, back);
  return *this;
}

template <typename T>
size_t Deque<T>::size() const {
  return sizedeque;
}

template <typename T>
bool Deque<T>::empty() {
  return (sizedeque == 0);
}

template <typename T>
T& Deque<T>::operator[](size_t index) {
  size_t place = first_arr * kCapacity + front + index;
  return deque[place / kCapacity][place % kCapacity];
}

template <typename T>
const T& Deque<T>::operator[](size_t index) const {
  size_t place = first_arr * kCapacity + front + index;
  return deque[place / kCapacity][place % kCapacity];
}

template <typename T>
T& Deque<T>::at(size_t index) {
  if (index >= sizedeque) {
    std::out_of_range("Out of range!");
  }
  return operator[](index);
}

template <typename T>
const T& Deque<T>::at(size_t index) const {
  if (index >= sizedeque) {
    std::out_of_range("Out of range!");
  }
  return operator[](index);
}

template <typename T>
void Deque<T>::push_back(const T& value) {
  if (sizedeque == 0) {
    new (deque[last_arr] + back) T(value);
    ++sizedeque;
    return;
  }

  if (last_arr == deque.size() - 1 && back == kCapacity - 1) {
    size_t prev_arr_size = deque.size();
    deque.resize(2 * deque.size());
    for (size_t i = prev_arr_size; i < deque.size(); ++i) {
      deque[i] = reinterpret_cast<T*>(new int8_t[kCapacity * sizeof(T)]);
    }
  }

  ++back;
  if (back == kCapacity) {
    ++last_arr;
    back = 0;
    if (!deque[last_arr]) {
      deque[last_arr] = reinterpret_cast<T*>(new int8_t[kCapacity * sizeof(T)]);
    }
  }

  new (deque[last_arr] + back) T(value);
  ++sizedeque;
}

template <typename T>
void Deque<T>::pop_back() {
  (deque[last_arr] + back)->~T();
  if (back == 0) {
    delete deque[last_arr];
    --last_arr;
    back = kCapacity;
  }
  --back;
  --sizedeque;
}

template <typename T>
void Deque<T>::push_front(const T& value) {
  if (sizedeque == 0) {
    new (deque[first_arr] + front) T(value);
    ++sizedeque;
    return;
  }

  if (first_arr == 0 && front == 0) {
    size_t prev_size = deque.size();
    vector<T*> new_deque(prev_size * 2);

    for (size_t i = 0; i < prev_size; i++) {
      new_deque[i + prev_size] = deque[i];
    }

    first_arr = prev_size - 1;
    last_arr += prev_size;
    front = kCapacity - 1;

    deque = new_deque;
    deque[first_arr] = reinterpret_cast<T*>(new int8_t[kCapacity * sizeof(T)]);
  } else if (first_arr != 0 && front == 0) {
    --first_arr;
    front = kCapacity - 1;

    deque[first_arr] = reinterpret_cast<T*>(new int8_t[kCapacity * sizeof(T)]);
  } else {
    --front;
  }

  new (deque[first_arr] + front) T(value);
  ++sizedeque;
}

template <typename T>
void Deque<T>::pop_front() {
  (deque[first_arr] + front)->~T();
  --sizedeque;
  ++front;

  if (front == kCapacity) {
    delete deque[first_arr];
    ++first_arr;
    front = 0;
  }
}