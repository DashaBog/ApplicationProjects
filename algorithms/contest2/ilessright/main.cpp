#include <iostream>
#include <vector>

void Merge(std::vector<std::pair<long long, long long>>& arr, int begin,
           int mid, int end, long long* inversions) {
  int firstiter = begin, seconditer = mid + 1;
  std::vector<std::pair<long long, long long>> merged;
  while (firstiter <= mid && seconditer <= end) {
    if (arr[firstiter].first > arr[seconditer].first) {
      merged.push_back(arr[firstiter]);
      inversions[arr[firstiter].second] =
          inversions[arr[firstiter].second] + end - seconditer + 1;
      ++firstiter;
    } else {
      merged.push_back(arr[seconditer]);
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

void MergeSort(std::vector<std::pair<long long, long long>>& arr, int begin,
               int end, long long* inversions) {
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
  std::vector<std::pair<long long, long long>> arr;
  for (int i = 0; i < n; i++) {
    long long first;
    std::cin >> first;
    arr.push_back(std::make_pair(first, i));
  }
  long long inversions[100001];
  for (int i = 0; i < 100001; ++i) {
    inversions[i] = 0;
  }
  MergeSort(arr, 0, n - 1, inversions);
  for (int i = 0; i < n; i++) {
    std::cout << inversions[i] << " ";
  }
  return 0;
}