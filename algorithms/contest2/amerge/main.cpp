#include <iostream>
#include <vector>

void Merge(std::vector<std::pair<long long, long long> >& arr, int begin,
           int mid, int end) {
  int firstiter = begin, seconditer = mid + 1;
  std::vector<std::pair<long long, long long> > merged;
  while (firstiter <= mid && seconditer <= end) {
    if (arr[firstiter].first < arr[seconditer].first) {
      merged.push_back(arr[firstiter]);
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

void MergeSort(std::vector<std::pair<long long, long long> >& arr, int begin,
               int end) {
  if (end - begin > 0) {
    int mid = (begin + end) / 2;
    MergeSort(arr, begin, mid);
    MergeSort(arr, mid + 1, end);
    Merge(arr, begin, mid, end);
  }
}

void MakeMashup(std::vector<std::pair<long long, long long> >& arr) {
  int i = 1, size = arr.size();
  int fixed = 0;
  while (i < (int)arr.size()) {
    if (arr[i].first <= arr[fixed].second) {
      if (arr[i].second > arr[fixed].second) {
        arr[fixed].second = arr[i].second;
      }
      arr[i].first = -1;
      --size;
    } else {
      fixed = i;
    }
    ++i;
  }

  std::cout << size << "\n";
  for (i = 0; i < (int)arr.size(); ++i) {
    if (arr[i].first != -1) {
      std::cout << arr[i].first << " " << arr[i].second << "\n";
    }
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::pair<long long, long long> > arr;
  for (int i = 0; i < n; i++) {
    long long first, second;
    std::cin >> first >> second;
    arr.push_back(std::make_pair(first, second));
  }
  MergeSort(arr, 0, n - 1);
  MakeMashup(arr);
  return 0;
}