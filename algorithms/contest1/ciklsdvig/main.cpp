#include <iostream>

int const* BinarySearchforShift(int const* begin, int const* end) {
  int mid = 0;
  while (end - begin > 1) {
    mid = (end - begin) / 2;
    if (*(begin + mid) < *begin) {
      end = begin + mid;
    } else {
      begin = begin + mid;
    }
  }
  if (end - begin == 1 && *end - *begin < 0) {
    begin = begin + 1;
  }
  return begin;
}

void EnterArray(int n, int* a) {
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
}

int main() {
  int n;
  std::cin >> n;
  int* a = new int[n + 1];
  EnterArray(n, a);
  std::cout << (BinarySearchforShift(a + 0, a + n) - a) % n;
  delete[](a);
  return 0;
}
