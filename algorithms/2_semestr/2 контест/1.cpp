#include <iostream>
#include <vector>

using std::vector;

void Bfs(vector<vector<std::pair<int,int>>> &g, vector<int> &dist, vector<int> &parent, vector<bool> &used, int s) {
  for (int i = 0; i < g.size(); ++i) {
    int v = -1;
    for (int j = 0; j < g.size(); ++j) {
      if (!used[j] && (v == -1 || dist[j] < dist[v])) {
        v = j;
      }
    }
    if (dist[v] >= INT32_MAX / 4) {
      break;
    }
    used[v] = true;
    for (size_t j = 0; j < g[v].size(); ++j) {
      int to = g[v][j].first;
      int len = g[v][j].second;
      if (dist[v] + len < dist[to]) {
        dist[to] = dist[v] + len;
        parent[to] = v;
      }
    }
  }
}


int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  int n = 0;
  std::cin >> n;

  int s = 0;
  int f = 0;
  std::cin >> s >> f;

  vector<vector<std::pair<int,int>>> g(n);
  vector<int> dist(n, INT32_MAX / 4);
  vector<int> parent(n);
  vector<bool> used(n, false);

  dist[s - 1] = 0;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int x = 0;
      std::cin >> x;
      if (x != -1) {
        g[i].emplace_back(j, x);
      }
    }
  }

  Bfs(g, dist, parent, used, s);
  if (dist[f - 1] >= INT32_MAX / 4) {
    std::cout << "-1" << std::endl;
  } else {
    std::cout << dist[f - 1] << std::endl;
  }

  return 0;
}
