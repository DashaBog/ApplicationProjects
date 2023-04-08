#include <iostream>

bool BinarySearch(int const* begin, int const* end, int target) {
  while (end - begin >= 1) {
    int mid = (end - begin) / 2;
    if (*(begin + mid) == target) {
      return true;
    }
    if (end - begin == 1) {
      return false;
    }
    if (*(begin + mid) > target) {
      end = begin + mid;
    } else if (*(begin + mid) < target) {
      begin = begin + mid;
    }
  }
  return false;
}

void EnterArray(int n, int* a) {
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
}

void ResultofBinSearch(int* a, int begin, int end, int target) {
  if (BinarySearch(a + begin, a + end, target)) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
}

int main() {
  int n;
  std::cin >> n;
  int* a = new int[n + 1];
  EnterArray(n, a);
  int numberofcalls;
  std::cin >> numberofcalls;
  for (int i = 0; i < numberofcalls; i++) {
    int begin = 0;
    int end = 0;
    int target = 0;
    std::cin >> begin >> end >> target;
    ResultofBinSearch(a, begin, end, target);
  }
  delete[](a);
  return 0;
}