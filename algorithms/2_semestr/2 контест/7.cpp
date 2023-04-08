#include <iostream>
#include <vector>

using std::vector;
using namespace std;

int Prima(vector<vector<int>> &g, int n) {
  int res = 0;
  vector<int> min(n, INT32_MAX);
  vector<int> sel(n, -1);
  vector<bool> used(n);

  min[0] = 0;

  for (int i = 0; i < n; ++i) {
    int v = -1;
    for (int j = 0; j < n; ++j)
      if (!used[j] && (v == -1 || min[j] < min[v]))
        v = j;

    used[v] = true;
    if (sel[v] != -1) {
      res += min[v];
    }

    for (int to = 0; to < n; ++to)
      if (g[v][to] < min[to]) {
        min[to] = g[v][to];
        sel[to] = v;
      }
  }
  return res;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  std::cin >> n;

  vector<vector<int>> g(n + 1, vector<int>(n + 1));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int w = 0;
      std::cin >> w;
      g[i][j] = w;
      if (i == j) {
        g[i][j] = INT32_MAX;
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    int cost = 0;
    std::cin >> cost;
    g[i][n] = cost;
    g[n][i] = cost;
  }
  g[n][n] = INT32_MAX;
  n += 1;

  int res = Prima(g, n);
  std::cout << res << std::endl;
  return 0;
}
