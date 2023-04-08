#include <iostream>
#include <vector>

int GetBucket(uint64_t numb, int index) { return (numb >> (8 * index) & 255); }

int main() {
  std::ios_base::sync_with_stdio(false);
  std::vector<uint64_t> arr;
  std::vector<uint64_t> buckets[256];
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    uint64_t cinx;
    std::cin >> cinx;
    arr.push_back(cinx);
  }
  for (int i = 0; i < 8; ++i) {
    for (int j = n - 1; j >= 0; --j) {
      buckets[GetBucket(arr[j], i)].push_back(arr[j]);
    }
    arr.clear();
    for (int i = 0; i < 256; ++i) {
      for (int j = buckets[i].size() - 1; j >= 0; --j) {
        arr.push_back(buckets[i][j]);
        buckets[i].pop_back();
      }
    }
  }
  for (int j = 0; j < n; ++j) {
    std::cout << arr[j] << "\n";
  }
  return 0;
}