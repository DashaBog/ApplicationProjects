#include <iostream>
#include <vector>

using std::vector;

void FloydWarshall(vector<vector<std::pair<int, int>>>& g, vector<int>& dist,
                   vector<int>& parent, size_t n, int& v) {
  for (size_t k = 0; k < n; ++k) {
    v = -1;
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < g[i].size(); ++j) {
        if (dist[i] < INT32_MAX) {
          if (dist[g[i][j].first] > dist[i] + g[i][j].second) {
            v = g[i][j].first;
            parent[g[i][j].first] = i;
            dist[g[i][j].first] =
                std::max(dist[i] + g[i][j].second, -INT32_MAX);
          }
        }
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  size_t n = 0;
  std::cin >> n;

  vector<vector<std::pair<int, int>>> g(n);

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      int w = 0;
      std::cin >> w;
      if (w != 100000) {
        g[i].emplace_back(j, w);
      }
    }
  }

  for (size_t i = 0; i < n; ++i) {
    vector<int> dist(n, INT32_MAX);
    vector<int> parent(n);
    int s = i + 1;
    dist[s - 1] = 0;
    parent[s - 1] = -1;
    int v;
    FloydWarshall(g, dist, parent, n, v);
    if (v != -1) {
      std::cout << "YES" << std::endl;
      int x = v;
      for (size_t j = 0; j < n; ++j) {
        x = parent[x];
      }
      vector<int> path;
      for (int cur = x;; cur = parent[cur]) {
        path.push_back(cur);
        if (cur == x && path.size() > 1) {
          break;
        }
      }
      std::cout << path.size() << std::endl;
      for (size_t i = path.size() - 1; i > 0; --i) {
        std::cout << path[i] + 1 << ' ';
      }
      std::cout << path[0] + 1;
      std::cout << std::endl;
      return 0;
    }
  }
  std::cout << "NO" << std::endl;

  return 0;
}