#include <algorithm>
#include <iostream>

bool Coverage(int const* arr, int n, int l, int k) {
  int ksi = 1;
  int ksh = arr[0];
  for (int i = 0; i < n; ++i) {
    if (arr[i] - ksh > l) {
      ++ksi;
      ksh = arr[i];
    }
  }
  return (ksi <= k);
}

int BinSearch(int* arr, int n, int k) {
  int begin = -1;
  int end = arr[n - 1] - arr[0];
  int mid = 0;
  while (end - begin > 1) {
    mid = (begin + end) / 2;
    if (Coverage(arr, n, mid, k)) {
      end = mid;
    } else {
      begin = mid;
    }
  }
  return end;
}

int main() {
  int n;
  int k;
  std::cin >> n >> k;
  int* arr = new int[n + 1];
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  std::sort(arr, arr + n);
  if (n == k) {
    std::cout << 0;
    delete[] arr;
    return 0;
  }

  std::cout << BinSearch(arr, n, k) << " ";
  delete[](arr);
  return 0;
}
