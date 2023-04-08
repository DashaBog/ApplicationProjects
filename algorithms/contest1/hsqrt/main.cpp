#include <cmath>
#include <iomanip>
#include <iostream>

void PrefixCalc(double* arr, int n, double* pref) {
  pref[0] = 1;
  for (int i = 1; i < n + 1; ++i) {
    pref[i] = pref[i - 1] * pow(arr[i - 1], 1.0 / 10000);
  }
}

double Sqrtn(double const* pref, int left, int right) {
  return pow(pref[right + 1] / pref[left], 10000.0 / (right - left + 1));
}

int main() {
  int n;
  std::cin >> n;
  double* arr = new double[n + 1];
  double* pref = new double[n + 1];
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  PrefixCalc(arr, n, pref);
  int q;
  std::cin >> q;
  std::cout << std::fixed << std::setprecision(6);
  for (int i = 0; i < q; ++i) {
    int left;
    int right;
    std::cin >> left >> right;
    double num = Sqrtn(pref, left, right);
    std::cout << num << "\n";
  }
  delete[](arr);
  delete[](pref);
  return 0;
}