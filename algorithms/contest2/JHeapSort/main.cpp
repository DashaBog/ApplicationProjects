#include <iostream>
#include <vector>

struct PosElem {
  int data;
  int posarr;
  int posinarr;
};

// HEAP

int Parent(int i) { return (i) / 2; }
int LeftChild(int i) { return (2 * i); }
int RightChild(int i) { return (2 * i + 1); }

void SiftUp(std::vector<PosElem>& v, int i) {
  while (Parent(i) >= 1 && v[i].data < v[Parent(i)].data) {
    if (i == 1) {
      break;
    }
    std::swap(v[i], v[Parent(i)]);
    i = Parent(i);
  }
}

void SiftDown(std::vector<PosElem>& v, int i) {
  while (2 * i <= (int)v.size() - 1) {
    int left = LeftChild(i);
    int right = RightChild(i);
    int mink = -1;
    if (v[left].data < v[i].data) {
      mink = left;
    }
    if (right <= (int)v.size() - 1 && v[right].data < v[i].data &&
        v[right].data < v[left].data) {
      mink = right;
    }
    if (mink == -1) {
      break;
    };
    std::swap(v[i], v[mink]);
    i = mink;
  }
}

void Insert(std::vector<PosElem>& v, PosElem x) {
  v.push_back(x);
  SiftUp(v, v.size() - 1);
}

PosElem GetMin(std::vector<PosElem>& v) { return v[1]; }

void ExtractMin(std::vector<PosElem>& v) {
  if (v.size() == 2) {
    v.pop_back();
    return;
  }
  v[1] = v[v.size() - 1];
  v.pop_back();
  SiftDown(v, 1);
}

// END OF HEAP

void TakeToHeap(std::vector<PosElem>& heap,
                std::vector<std::vector<long long> >& arr) {
  PosElem first;
  first.data = -1;
  first.posarr = -1;
  first.posinarr = -1;
  Insert(heap, first);
  for (int i = 1; i <= (int)arr.size(); ++i) {
    PosElem current;
    current.data = arr[i - 1][0];
    current.posinarr = 0;
    current.posarr = i - 1;
    Insert(heap, current);
  }
}

void TakeToSorted(std::vector<PosElem>& heap,
                  std::vector<std::vector<long long> >& arr,
                  std::vector<long long>& sorted) {
  while (heap.size() != 1) {
    PosElem current = GetMin(heap);
    ExtractMin(heap);
    sorted.push_back(current.data);
    if (current.posinarr + 1 < (int)arr[current.posarr].size()) {
      PosElem next;
      next.data = arr[current.posarr][current.posinarr + 1];
      next.posarr = current.posarr;
      next.posinarr = current.posinarr + 1;
      Insert(heap, next);
    }
  }
  for (int i = 1; i < (int)sorted.size(); ++i) {
    std::cout << sorted[i] << " ";
  }
}

int main() {
  int k;
  std::cin >> k;
  std::vector<std::vector<long long> > arr;
  for (int i = 0; i < k; ++i) {
    int n;
    std::cin >> n;
    std::vector<long long> cinx;
    for (int j = 0; j < n; ++j) {
      int el;
      std::cin >> el;
      cinx.push_back(el);
    }
    arr.push_back(cinx);
  }
  std::vector<PosElem> heap;
  TakeToHeap(heap, arr);
  std::vector<long long> sorted;
  sorted.push_back(-1);
  TakeToSorted(heap, arr, sorted);
  return 0;
}