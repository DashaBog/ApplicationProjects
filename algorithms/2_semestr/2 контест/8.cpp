#include <iostream>
#include <vector>
#include <cmath>

using std::vector;

double Prima(vector<vector<double>> &g, int n) {
  double res = 0;
  vector<double> min(n, INT32_MAX);
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

double dist(std::pair<int, int> a, std::pair<int, int> b) {
  return sqrt((b.first - a.first) * (b.first - a.first) + (b.second - a.second) * (b.second - a.second));
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  std::cin >> n;

  vector<std::pair<int, int>> coord;
  for (int i = 0; i < n; ++i) {
    int x = 0;
    int y = 0;
    std::cin >> x >> y;
    coord.emplace_back(x, y);
  }

  vector<vector<double>> g(n, vector<double>(n));

  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      if (i == j) {
        g[i][j] = 0;
      } else {
        g[i][j] = dist(coord[i], coord[j]);
        g[j][i] = dist(coord[i], coord[j]);
      }
    }
  }

  double res = Prima(g, n);
  std::cout << std::fixed;
  std::cout.precision(9);
  std::cout << res << std::endl;
  return 0;
}
