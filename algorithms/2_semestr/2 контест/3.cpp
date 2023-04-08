#include <iostream>
#include <vector>

using std::vector;

void Bfs(vector<vector<std::pair<int, int>>> &g, vector<int> &dist, int n) {
  for (size_t k = 0; k < n - 1; ++k) {
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < g[i].size(); ++j) {
        if (dist[i] >= 0 && dist[i] < 30000) {
          if (dist[g[i][j].first] > dist[i] + g[i][j].second) {
            dist[g[i][j].first] = dist[i] + g[i][j].second;
          }
        }
      }
    }
  }
}


int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  vector<vector<std::pair<int, int>>> g(n);
  vector<int> dist(n, 30000);

  int s = 1;
  dist[s - 1] = 0;

  for (int i = 0; i < m; ++i) {
    int x = 0;
    int y = 0;
    int w = 0;
    std::cin >> x >> y >> w;
    g[x - 1].emplace_back(y - 1, w);
  }

  Bfs(g, dist, n);
  for (int i = 0; i < n; ++i){
    std::cout << dist[i] << " ";
  }
  std::cout << std::endl;

  return 0;
}
