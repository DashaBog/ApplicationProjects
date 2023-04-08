#pragma once

#include <cstddef>
#include <vector>

class RingBuffer {
 public:
  explicit RingBuffer(size_t capacity) { capacity_ = capacity; }

  size_t Size() const { return buffer_.size(); }

  bool Empty() const { return buffer_.empty(); }

  bool TryPush(int element) {
    if (Size() < capacity_) {
      buffer_.push_back(element);
      return true;
    }
    return false;
  }

  bool TryPop(int* element) {
    if (!Empty()) {
      *element = buffer_[0];
      buffer_.erase(buffer_.begin());
      return true;
    }
    return false;
  }

 private:
  std::vector<int> buffer_;
  size_t capacity_;
};

int main() {
  RingBuffer buffer(1);
  return 0;
}
