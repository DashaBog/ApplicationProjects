#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using std::vector;

int Kruskal(vector<std::pair<int, std::pair<int, int>>> &g, int n) {
  int res = 0;
  std::sort(g.begin(), g.end());
  vector<int> tree_id(n);

  for (int i = 0; i < n; ++i) {
    tree_id[i] = i;
  }

  for (size_t i = 0; i < g.size(); ++i) {
    int a = g[i].second.first;
    int b = g[i].second.second;
    int l = g[i].first;
    if (tree_id[a] != tree_id[b]) {
      res += l;
      int old_id = tree_id[b];
      int new_id = tree_id[a];
      for (int j = 0; j < n; ++j)
        if (tree_id[j] == old_id)
          tree_id[j] = new_id;
    }
  }
  return res;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  vector<std::pair<int, std::pair<int, int>>> g;

  for (int i = 0; i < m; ++i) {
    int x = 0;
    int y = 0;
    int w = 0;
    std::cin >> x >> y >> w;
    std::pair<int, int> e = std::make_pair(x - 1, y - 1);
    g.emplace_back(w, e);
  }

  int res = Kruskal(g, n);

  std::cout << res << std::endl;

  return 0;
}
