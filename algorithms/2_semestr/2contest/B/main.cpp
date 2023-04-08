#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <vector>

using std::vector;

void Dijkstra(vector<vector<std::pair<int64_t, int64_t>>>& g,
              vector<int64_t>& dist, int64_t s) {
  std::set<std::pair<int64_t, int64_t>> q;
  q.insert(std::make_pair(dist[s], s));
  while (!q.empty()) {
    int64_t v = q.begin()->second;
    q.erase(q.begin());

    for (size_t i = 0; i < g[v].size(); ++i) {
      int64_t to = g[v][i].first;
      int64_t len = g[v][i].second;
      if (dist[v] + len < dist[to]) {
        q.erase(std::make_pair(dist[to], to));
        dist[to] = dist[v] + len;
        q.insert(std::make_pair(dist[to], to));
      }
    }
  }
}

int main() {
  const int64_t kInf = std::numeric_limits<int64_t>::max();
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  size_t vertex_num = 0;
  size_t edges_num = 0;
  size_t k_num = 0;

  std::cin >> vertex_num >> edges_num >> k_num;

  std::vector<int64_t> pains;
  for (size_t i = 0; i < k_num; ++i) {
    int64_t pain;
    std::cin >> pain;
    pains.push_back(pain - 1);
  }

  vector<vector<std::pair<int64_t, int64_t>>> list(vertex_num);
  for (size_t i = 0; i < edges_num; ++i) {
    int64_t x = 0;
    int64_t y = 0;
    int64_t w = 0;
    std::cin >> x >> y >> w;
    list[x - 1].emplace_back(y - 1, w);
    list[y - 1].emplace_back(x - 1, w);
  }
  int64_t you;
  int64_t s;
  std::cin >> you >> s;
  s--;
  you--;
  vector<int64_t> dist(vertex_num, kInf);

  dist[s] = 0;

  Dijkstra(list, dist, s);

  bool path = true;
  for (size_t it = 0; it < pains.size(); it++) {
    if (dist[you] >= dist[pains[it]]) {
      std::cout << "-1";
      path = false;
      break;
    }
  }
  if (path) {
    std::cout << dist[you];
  }
  return 0;
}