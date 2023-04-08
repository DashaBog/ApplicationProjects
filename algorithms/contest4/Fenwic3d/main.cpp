#include <iostream>
#include <vector>
using std::vector;

void Update(vector<vector<vector<long long>>>& tree, long long x, long long y,
            long long z, long long changed, long long size) {
  for (long long i = x; i < size; i = (i | (i + 1))) {
    for (long long j = y; j < size; j = (j | (j + 1))) {
      for (long long k = z; k < size; k = (k | (k + 1))) {
        tree[i][j][k] += changed;
      }
    }
  }
}

long long GetSum(vector<vector<vector<long long>>>& tree, long long x,
                 long long y, long long z) {
  long long result = 0;
  for (long long i = x; i >= 0; i = (i & (i + 1)) - 1) {
    for (long long j = y; j >= 0; j = (j & (j + 1)) - 1) {
      for (long long k = z; k >= 0; k = (k & (k + 1)) - 1) {
        result += tree[i][j][k];
      }
    }
  }
  return result;
}

int main() {
  int fenwicksize = 0;
  std::cin >> fenwicksize;
  vector<vector<vector<long long>>> fenwicktree(
      fenwicksize, vector<vector<long long>>(
                       fenwicksize, vector<long long>(fenwicksize, 0)));
  int request = 0;
  const int kUpdate = 1;
  const int kGetSum = 2;
  const int kQuit = 3;
  while (request != kQuit) {
    std::cin >> request;
    if (request == kUpdate) {
      long long x = 0;
      long long y = 0;
      long long z = 0;
      long long k = 0;
      std::cin >> x >> y >> z >> k;
      Update(fenwicktree, x, y, z, k, fenwicksize);
    } else if (request == kGetSum) {
      long long x1 = 0;
      long long y1 = 0;
      long long z1 = 0;
      long long x2 = 0;
      long long y2 = 0;
      long long z2 = 0;
      std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
      long long sum = GetSum(fenwicktree, x2, y2, z2) -
                      GetSum(fenwicktree, x1 - 1, y2, z2) -
                      GetSum(fenwicktree, x2, y1 - 1, z2) -
                      GetSum(fenwicktree, x2, y2, z1 - 1) +
                      GetSum(fenwicktree, x1 - 1, y1 - 1, z2) +
                      GetSum(fenwicktree, x2, y1 - 1, z1 - 1) +
                      GetSum(fenwicktree, x1 - 1, y2, z1 - 1) -
                      GetSum(fenwicktree, x1 - 1, y1 - 1, z1 - 1);
      std::cout << sum << "\n";
    }
  }
  return 0;
}