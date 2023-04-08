#include <iostream>
#include <vector>

int Parent(int i) { return (i) / 2; }
int LeftChild(int i) { return (2 * i); }
int RightChild(int i) { return (2 * i + 1); }

void SiftUp(std::vector<std::pair<long long, long long>>& v, int i) {
  while (Parent(i) >= 1 && v[i] < v[Parent(i)]) {
    if (i == 1) {
      break;
    }
    std::swap(v[i], v[Parent(i)]);
    i = Parent(i);
  }
}

void SiftDown(std::vector<std::pair<long long, long long>>& v, int i) {
  while (2 * i <= (int)v.size() - 1) {
    int left = LeftChild(i);
    int right = RightChild(i);
    int mink = -1;
    if (v[left] < v[i]) {
      mink = left;
    }
    if (right <= (int)v.size() - 1 && v[right] < v[i] && v[right] < v[left]) {
      mink = right;
    }
    if (mink == -1) {
      break;
    };
    std::swap(v[i], v[mink]);
    i = mink;
  }
}

void Insert(std::vector<std::pair<long long, long long>>& v, int x, int zap) {
  v.push_back(std::make_pair(x, zap));
  SiftUp(v, v.size() - 1);
}

long long GetMin(std::vector<std::pair<long long, long long>>& v) {
  return v[1].first;
}

void ExtractMin(std::vector<std::pair<long long, long long>>& v) {
  if (v.size() == 2) {
    v.pop_back();
    return;
  }
  v[1] = v[v.size() - 1];
  v.pop_back();
  SiftDown(v, 1);
}

void DecreaseKey(std::vector<std::pair<long long, long long>>& v, int k,
                 int del) {
  for (size_t i = 1; i <= v.size(); ++i) {
    if (v[i].second == k) {
      v[i].first -= del;
      SiftUp(v, i);
      break;
    }
  }
}

void Cinx(std::vector<std::pair<long long, long long>>& v) {
  int n = 0, zap = 0;
  std::cin >> n;
  std::string s;
  for (int i = 0; i < n; i++) {
    std::cin >> s;
    if (s == "getMin") {
      ++zap;
      std::cout << GetMin(v) << "\n";
    } else if (s == "extractMin") {
      ++zap;
      ExtractMin(v);
    } else if (s == "insert") {
      ++zap;
      long long k;
      std::cin >> k;
      Insert(v, k, zap);
    } else if (s == "decreaseKey") {
      ++zap;
      int k;
      int del;
      std::cin >> k >> del;
      DecreaseKey(v, k, del);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::vector<std::pair<long long, long long>> v;
  v.push_back(std::make_pair(-1, 0));
  Cinx(v);
  return 0;
}
