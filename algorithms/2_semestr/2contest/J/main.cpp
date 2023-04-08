#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using std::vector, std::min, std::pair, std::set;

int Dijkstra(vector<vector<pair<int, int>>>& g, int n, int max_deck, int u,
             int d) {
  set<pair<int, int>> q;
  vector<int> dist(g.size(), INT32_MAX);
  dist[0] = 0;
  q.insert(std::make_pair(dist[0], 0));
  while (!q.empty()) {
    int v = q.begin()->second;
    q.erase(q.begin());

    if (v < max_deck) {
      if (v > 0 && dist[v - 1] > dist[v] + d) {
        q.erase(std::make_pair(dist[v - 1], v - 1));
        dist[v - 1] = dist[v] + d;
        q.insert(std::make_pair(dist[v - 1], v - 1));
      }

      if (v < max_deck && dist[v + 1] > dist[v] + u) {
        q.erase(std::make_pair(dist[v + 1], v + 1));
        dist[v + 1] = dist[v] + u;
        q.insert(std::make_pair(dist[v + 1], v + 1));
      }
    }

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

  return dist[n - 1];
}

int main() {
  int n, u, d, i, j, l;
  std::cin >> n >> u >> d >> i >> j >> l;
  vector<vector<pair<int, int>>> graph(1000000 + l, vector<pair<int, int>>());
  int max_deck = n;
  for (int ind = 0; ind < l; ++ind) {
    int k, deck;
    std::cin >> k;
    for (int jnd = 0; jnd < k; ++jnd) {
      std::cin >> deck;
      max_deck = std::max(max_deck, deck);
      graph[deck - 1].emplace_back(1000000 + ind, i);
      graph[1000000 + ind].emplace_back(deck - 1, j);
    }
  }
  std::cout << Dijkstra(graph, n, max_deck, u, d);
  return 0;
}