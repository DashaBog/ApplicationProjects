#include <iostream>
#include <vector>
#include <queue>
#include <set>

using std::vector;

void Bfs(vector<vector<std::pair<int,int>>> &g, vector<int> &dist, int s) {
  std::set <std::pair<int, int>> q;
  q.insert(std::make_pair(dist[s], s));
  while(!q.empty()) {
    int v = q.begin()->second;
    q.erase(q.begin());

    for (size_t i = 0; i < g[v].size(); ++i) {
      int to = g[v][i].first;
      int len = g[v][i].second;
      if (dist[v] + len < dist[to]) {
        q.erase(std::make_pair(dist[to], to));
        dist[to] = dist[v] + len;
        q.insert(std::make_pair(dist[to], to));
      }
    }
  }
}


int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int nm = 0;
  std::cin >> nm;

  for (int k = 0; k < nm; ++k) {
    int n = 0;
    int m = 0;
    std::cin >> n >> m;

    vector<vector<std::pair<int,int>>> g(n);

    for (int i = 0; i < m; ++i) {
      int x = 0;
      int y = 0;
      int w = 0;
      std::cin >> x >> y >> w;
      g[x].emplace_back(y, w);
      g[y].emplace_back(x, w);
    }

    int s = 0;
    std::cin >> s;

    vector<int> dist(n, 2009000999);

    dist[s] = 0;

    Bfs(g, dist, s);

    for (int f = 0; f < n; ++f) {
      std::cout << dist[f] << ' ';
    }
    std::cout << std::endl;
  }

  return 0;
}
