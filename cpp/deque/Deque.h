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
    size_t index;
    std::conditional_t<IsConst, const Deque<T>*, Deque<T>*> deq;

    Iterator() = default;

    ~Iterator() = default;

    Iterator(size_t index,
             std::conditional_t<IsConst, const Deque<T>*, Deque<T>*> deq)
        : index(index), deq(deq) {}

    Iterator(const Iterator& iter) {
      if (this == &iter) {
        return;
      }
      index = iter.index;
      deq = iter.deq;
    }

    Iterator& operator=(const Iterator& iter) {
      if (this == &iter) {
        return *this;
      }
      index = iter.index;
      deq = iter.deq;
      return *this;
    }

    Iterator operator-(int value) const {
      int new_index = (index - value);
      return Iterator(new_index, this->deq);
    }

    Iterator operator+(int value) const { return *this - (-value); }

    Iterator& operator+=(int value) {
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
      return *(deq->deque[index]);
    }

    std::conditional_t<IsConst, const T*, T*> operator->() const {
      return deq->deque[index];
    }

    bool operator==(const Iterator& iter) const {
      return (this->index == iter.index);
    }

    bool operator<(const Iterator& iter) const {
      return (this->index < iter.index);
    }

    bool operator!=(const Iterator& iter) const { return !(*this == iter); }

    bool operator>=(const Iterator& iter) const { return !(*this < iter); }

    bool operator<=(const Iterator& iter) const {
      return (*this == iter) || (*this < iter);
    }

    bool operator>(const Iterator& iter) const { return !(*this <= iter); }

    int64_t operator-(const Iterator& iter) const {
      return (index - iter.index);
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

  iterator begin() { return iterator(front, this); }

  const_iterator cbegin() const { return const_iterator(front, this); }

  iterator end() {
    auto copy = iterator(back, this);
    if (!empty()) {
      ++copy;
    }
    return copy;
  }

  const_iterator cend() const {
    auto copy = const_iterator(back, this);
    if (sizedeque != 0) {
      ++copy;
    }
    return copy;
  }

  reverse_iterator rbegin() { return reverse_iterator(end()); }

  reverse_iterator rend() { return reverse_iterator(begin()); }

  const_reverse_iterator rbegin() const { return reverse_iterator(cend()); }

  const_reverse_iterator rend() const { return reverse_iterator(cbegin()); }

  const_reverse_iterator crbegin() const { return reverse_iterator(cend()); }

  const_reverse_iterator crend() const { return reverse_iterator(cbegin()); }

  void insert(const iterator& iter, const T& value) {
    push_back(value);
    for (size_t i = back; i > static_cast<size_t>(iter.index); --i) {
      std::swap(deque[i], deque[i - 1]);
    }
  }

  void erase(const iterator& iter) {
    for (size_t i = static_cast<size_t>(iter.index); i < back; ++i) {
      std::swap(deque[i], deque[i + 1]);
    }
    pop_back();
  }

  vector<T*> deque;
  size_t front = 0;
  size_t back = 0;
  size_t sizedeque = 0;
  const size_t kInicialCapacity = 102;
  size_t capacity = kInicialCapacity;
};

template <typename T>
Deque<T>::Deque() {
  deque.resize(capacity);
}

template <typename T>
Deque<T>::~Deque() {
  for (size_t i = 0; i < capacity; ++i) {
    if (deque[i] != nullptr) {
      delete (deque[i]);
    }
  }
}

template <typename T>
Deque<T>::Deque(const Deque& dequet)
    : front(dequet.front),
      back(dequet.back),
      sizedeque(dequet.sizedeque),
      capacity(dequet.capacity) {
  this->deque.resize(capacity);
  for (size_t i = 0; i < sizedeque; ++i) {
    deque[i + front] = new T(dequet[i + front]);
  }
}

template <typename T>
Deque<T>::Deque(size_t count) : front(0), back(count - 1), sizedeque(count) {
  capacity = count;
  deque.resize(capacity);
  for (size_t i = front; i <= back; ++i) {
    deque[i] = new T(0);
  }
}

template <typename T>
Deque<T>::Deque(size_t count, const T& value)
    : front(0), back(count - 1), sizedeque(count) {
  capacity = count;
  deque.resize(capacity);
  for (size_t i = 0; i <= back; ++i) {
    deque[i] = new T(value);
  }
}

template <typename T>
Deque<T>& Deque<T>::operator=(const Deque& other) {
  Deque copy = Deque(other);
  std::swap(copy.sizedeque, sizedeque);
  std::swap(copy.deque, deque);
  std::swap(copy.front, front);
  std::swap(copy.back, back);
  std::swap(copy.capacity, capacity);
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
  return *(deque[index]);
}

template <typename T>
const T& Deque<T>::operator[](size_t index) const {
  return *(deque[index]);
}

template <typename T>
T& Deque<T>::at(size_t index) {
  if (index >= sizedeque) {
    throw std::out_of_range("Out of range!");
  }
  return operator[](index);
}

template <typename T>
const T& Deque<T>::at(size_t index) const {
  if (index >= sizedeque) {
    throw std::out_of_range("Out of range!");
  }
  return operator[](index);
}

template <typename T>
void Deque<T>::push_back(const T& value) {
  if (sizedeque == 0) {
    ++sizedeque;
    deque[0] = new T(value);
    return;
  }
  if (back == capacity - 1) {
    capacity *= 2;
    deque.resize(capacity);
  }
  deque[back + 1] = new T(value);
  ++back;
  ++sizedeque;
}

template <typename T>
void Deque<T>::pop_back() {
  delete (deque[back]);
  deque[back] = nullptr;
  --back;
  --sizedeque;
}

template <typename T>
void Deque<T>::push_front(const T& value) {
  if (front == 0) {
    vector<T*> new_deque(capacity * 2);

    for (size_t i = front; i <= back; i++) {
      new_deque[i + capacity] = deque[i];
    }
    back += capacity;
    front += capacity - 1;
    capacity *= 2;
    std::swap(deque, new_deque);
  } else {
    --front;
  }
  deque[front] = new T(value);
  ++sizedeque;
}

template <typename T>
void Deque<T>::pop_front() {
  delete (deque[front]);
  deque[front] = nullptr;
  --sizedeque;
  ++front;
}