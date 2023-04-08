#include <iostream>
#include <vector>

using std::vector;

struct Edge {
  int start, finish, weisht;
};

void Solve(vector<Edge>& list, size_t vertex_num, size_t edge_num) {
  vector<int> dist(vertex_num, 30000);
  dist[0] = 0;
  for (size_t i = 0; i < vertex_num - 1; ++i) {
    for (size_t j = 0; j < edge_num; ++j) {
      if (dist[list[j].start] < 30000) {
        dist[list[j].finish] = std::min(dist[list[j].finish],
                                        dist[list[j].start] + list[j].weisht);
      }
    }
  }
  for (size_t i = 0; i < vertex_num; ++i) {
    std::cout << dist[i] << " ";
  }
  std::cout << std::endl;
}

int main() {
  size_t vertex_num = 0;
  size_t edges_num = 0;
  std::cin >> vertex_num >> edges_num;

  vector<Edge> list(edges_num);

  for (size_t i = 0; i < edges_num; ++i) {
    int64_t x = 0;
    int64_t y = 0;
    int64_t w = 0;
    std::cin >> x >> y >> w;
    Edge aa;
    aa.start = x - 1;
    aa.finish = y - 1;
    aa.weisht = w;
    list[i] = aa;
    //list[x - 1].emplace_back(y - 1, w);
  }

  Solve(list, vertex_num, edges_num);
  return 0;
}

/*#include <iostream>
#include <vector>

using std::vector;

void FordBellmann(vector<vector<std::pair<int64_t, int64_t>>>& list,
         vector<int64_t>& dist, size_t n) {
  for (size_t k = 0; k < n - 1; ++k) {
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < list[i].size(); ++j) {
        if (dist[i] >= 0 && dist[i] < 30000) {
          if (dist[list[i][j].first] > dist[i] + list[i][j].second) {
            dist[list[i][j].first] = dist[i] + list[i][j].second;
          }
        }
      }
    }
  }
}

int main() {
  size_t vertex_num = 0;
  size_t edges_num = 0;
  std::cin >> vertex_num >> edges_num;

  vector<vector<std::pair<int64_t, int64_t>>> list(vertex_num);
  vector<int64_t> dist(vertex_num, 30000);

  int64_t s = 1;
  dist[s - 1] = 0;

  for (size_t i = 0; i < edges_num; ++i) {
    int64_t x = 0;
    int64_t y = 0;
    int64_t w = 0;
    std::cin >> x >> y >> w;
    list[x - 1].emplace_back(y - 1, w);
  }

  FordBellmann(list, dist, vertex_num);
  for (size_t i = 0; i < vertex_num; ++i) {
    std::cout << dist[i] << " ";
  }
  std::cout << std::endl;

  return 0;
}*/