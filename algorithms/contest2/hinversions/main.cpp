#include <iostream>
#include <vector>

void Merge(std::vector<long long>& arr, int begin, int mid, int end,
           long long* inversions) {
  int firstiter = begin, seconditer = mid + 1;
  std::vector<long long> merged;
  while (firstiter <= mid && seconditer <= end) {
    if (arr[firstiter] <= arr[seconditer]) {
      merged.push_back(arr[firstiter]);
      ++firstiter;
    } else {
      merged.push_back(arr[seconditer]);
      *inversions = *inversions + mid - firstiter + 1;
      ++seconditer;
    }
  }
  while (firstiter <= mid) {
    merged.push_back(arr[firstiter]);
    ++firstiter;
  }
  while (seconditer <= end) {
    merged.push_back(arr[seconditer]);
    ++seconditer;
  }
  for (int i = begin; i <= end; ++i) {
    arr[i] = merged[i - begin];
  }
}

void MergeSort(std::vector<long long>& arr, int begin, int end,
               long long* inversions) {
  if (end - begin > 0) {
    int mid = (begin + end) / 2;
    MergeSort(arr, begin, mid, inversions);
    MergeSort(arr, mid + 1, end, inversions);
    Merge(arr, begin, mid, end, inversions);
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<long long> arr;
  for (int i = 0; i < n; i++) {
    long long first;
    std::cin >> first;
    arr.push_back(first);
  }
  long long inversions = 0;
  MergeSort(arr, 0, n - 1, &inversions);
  std::cout << inversions << "\n";
  return 0;
}