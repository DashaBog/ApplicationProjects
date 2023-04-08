#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <queue>

void DsuMake (int v, std::vector<int> &parent) {
  parent[v] = v;
}

int DsuGet(int v, std::vector<int>& parent) {
  if (v == parent[v]){
    return v;
  }
  return parent[v] = DsuGet(parent[v], parent);}

void DsuUnite(int x, int y, std::vector<int>& parent) {
  x = DsuGet(x, parent);
  y = DsuGet(y, parent);
  if (x != y)
    parent[x] = y;
}

void Bfs(int a, std::vector<std::vector<std::pair<int, int>>>& g, std::vector<std::vector<int>>& dist) {
  std::queue<int> q;
  std::vector<bool> used(g.size());
  q.push(a);
  used[a] = true;
  dist[a][a] = INT32_MAX / 3;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (size_t i = 0; i < g[v].size(); ++i) {
      int to = g[v][i].first;
      if (!used[to]) {
        q.push(to);
        used[to] = true;
        dist[a][to] = std::min(dist[a][v], g[v][i].second);
        dist[a][to] = std::min(dist[a][v], g[v][i].second);
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  int m = 0;
  int k = 0;
  std::cin >> n >> m >> k;

  std::vector<std::pair<int, std::pair<int, int>>> g;

  for (int i = 0; i < m; ++i) {
    int x = 0;
    int y = 0;
    int w = 0;
    std::cin >> x >> y >> w;
    std::pair<int, int> e = std::make_pair(x - 1, y - 1);
    g.emplace_back(-w, e);
  }

  std::sort(g.begin(), g.end());

  std::vector<int> parent(n + 1);

  for (int i = 0; i < n + 1; ++i) {
    DsuMake(i, parent);
  }

  std::vector<std::vector<std::pair<int, int>>> tree(n);

  for (int i = 0; i < m; ++i) {
    if (DsuGet(g[i].second.first, parent) != DsuGet(g[i].second.second, parent)) {
      tree[g[i].second.first].emplace_back(g[i].second.second, -g[i].first);
      tree[g[i].second.second].emplace_back(g[i].second.first, -g[i].first);
      DsuUnite(g[i].second.first, g[i].second.second, parent);
    }
  }

  std::vector<std::vector<int>> dist(n, std::vector<int>(n));

  for (int i = 0; i < n; ++i) {
    Bfs(i, tree, dist);
  }

  for (int i = 0; i < k; ++i) {
    int x = 0;
    int y = 0;
    std::cin >> x >> y;
    std::cout << dist[x - 1][y - 1] << "\n";
  }

  return 0;
}