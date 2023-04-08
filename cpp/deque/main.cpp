#include <iostream>
#include "Deque.h"

struct NotDefaultConstructible {
  NotDefaultConstructible() = delete;
  NotDefaultConstructible(int data) : data(data) {}
  int data;
  auto operator<=>(const NotDefaultConstructible&) const = default;
};

int main() {

  Deque<NotDefaultConstructible> d(10000, {1});
  auto start_size = d.size();

  d.insert(d.begin() + static_cast<int>(start_size) / 2,
           NotDefaultConstructible{2});
  // std::cout <<(d.size() == start_size + 1);
  d.erase(d.begin() + static_cast<int>(start_size) / 2 - 1);
  // std::cout <<(d.size() == start_size);

  // std::cout <<(size_t(std::count(d.begin(), d.end(), NotDefaultConstructible{1}))
  //                 == start_size - 1);
  // std::cout <<(std::count(d.begin(), d.end(), NotDefaultConstructible{2}) == 1);

  Deque<NotDefaultConstructible> copy;
  for (const auto& item: d) {
    copy.insert(copy.end(), item);
  }

  Deque<NotDefaultConstructible>::iterator iter = d.begin();
  Deque<NotDefaultConstructible>::iterator iter1 = d.end();
  Deque<NotDefaultConstructible>::iterator iter2 = copy.begin();
  std::cout << (iter == iter1) << " " << (iter1 == iter2) << " " << (iter == iter2) << "\n";
/*  std::cout <<(d.size() == copy.size());
  std::cout <<(std::equal(d.begin(), d.end(), copy.begin()));*/

return 0;
}
