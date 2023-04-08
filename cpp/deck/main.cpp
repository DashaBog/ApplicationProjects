#include <iostream>
#include "Deque.h"

using namespace std;

struct NotDefaultConstructible {
  NotDefaultConstructible() = delete;
  NotDefaultConstructible(int data) : data(data) {}
  int data;

  auto operator<=> (const NotDefaultConstructible&) const = default;
};


int main() {

  using T1 = int;
  auto test = std::is_constructible_v<Deque<T1>, size_t, const T1&>;
  std::cout << test;

  /*Deque<int> test(5, 6);
  Deque<int>::iterator it = test.begin();
  Deque<int>::iterator itend = test.end();
  Deque<int>::const_iterator cit = test.cbegin();// {test.first_arr, test.front, test.deque_};
  Deque<int>::const_iterator citend = test.cend();// {test.first_arr, test.front, test.deque_};
  it++;
  citend--;
  --itend;
  ++cit;
  cout << *it << *cit << *citend << *itend << std::endl;
  cout << (it < itend) << (cit >= citend) << (itend==itend) << std::endl;
  cout << (it > itend) << (cit <= citend) << (itend!=itend) << std::endl;
  cout << (itend - it) << std::endl;*/
  return 0;
}
