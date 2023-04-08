#include <iostream>

void PrefixCalc(int* arr, int n, int* pref) {
  pref[0] = arr[0];
  for (int i = 1; i < n + 1; ++i) {
    pref[i] = std::min(pref[i - 1], arr[i - 1]);
  }
}

void PostfixCalc(int* arr, int n, int* post) {
  post[n - 1] = arr[n - 1];
  for (int i = n - 2; i >= 0; --i) {
    post[i] = std::min(post[i + 1], arr[i]);
  }
}

void ResultMin(int* pref, int* post, int l, int r) {
  std::cout << std::min(pref[l], post[r - 1]) << "\n";
}

int main() {
  int n;
  std::cin >> n;
  int* arr = new int[n + 1];
  int* pref = new int[n + 1];
  int* post = new int[n + 1];
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  PrefixCalc(arr, n, pref);
  PostfixCalc(arr, n, post);
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    int left;
    int right;
    std::cin >> left >> right;
    ResultMin(pref, post, left, right);
  }
  delete[](arr);
  delete[](pref);
  delete[](post);
  return 0;
}
