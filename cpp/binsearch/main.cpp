#include <algorithm>
#include <iostream>
#include <vector>

int* LowerBound(int* first, int* last, int value) {
  int* mid = first;
  int* size = last;
  while (first < last) {
    mid = first + (last - first) / 2;
    if (value <= *mid) {
      last = mid;
    } else {
      first = mid + 1;
    }
  }
  if (first < size && *first < value) {
    first = first + 1;
  }
  return first;
}

int main()
{
  int size = 7;
  int arr[] = {1, 2, 3, 4, 5, 6, 7};

  int* begin = arr;
  int* end = arr + size;

  int* ptr = LowerBound(arr, arr + size, 1);
  std::cout << *ptr;
  return 0;
}
