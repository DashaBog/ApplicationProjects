#include <iostream>
#include <vector>
#include <queue>

using std::vector;

vector<int> tin, tout;
int timer;
vector <vector<int>> up;

std::vector<int> Bfs(vector<vector<int>> &g, int a) {
  std::queue<int> q;
  std::vector<bool> used(g.size());
  used[a - 1] = true;
  std::vector<int> dist(g.size());

  q.push(a - 1);
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (size_t i = 0; i < g[v].size(); ++i) {
      int to = g[v][i];
      if (!used[to]) {
        used[to] = true;
        q.push(to);
        dist[to] = dist[v] + 1;
      }
    }
  }
  return dist;
}

void Dfs(int v, int p, int l, std::vector<std::vector<int>>& g) {
  tin[v] = ++timer;
  up[v][0] = p;
  for (int i = 1; i <= l; ++i) {
    up[v][i] = up[up[v][i - 1]][i - 1];
  }
  for (size_t i = 0; i < g[v].size(); ++i) {
    int to = g[v][i];
    if (to != p) {
      Dfs(to, v, l, g);
    }
  }
  tout[v] = ++timer;
}

bool Upper(int a, int b) {
  return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int Lca(int a, int b, int l) {
  if (Upper(a, b)) {
    return a;
  }
  if (Upper(b, a)) {
    return b;
  }
  for (int i = l; i >= 0; --i) {
    if (!Upper(up[a][i], b)) {
      a = up[a][i];
    }
  }
  return up[a][0];
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  std::cin >> n;

  std::vector<std::vector<int>> tree(n);

  for (int i = 0; i < n - 1; ++i) {
    int x = 0;
    int y = 0;
    std::cin >> x >> y;
    tree[x - 1].emplace_back(y - 1);
    tree[y - 1].emplace_back(x - 1);
  }

  tin.resize(n), tout.resize(n), up.resize(n);

  int l = 1;
  while ((1 << l) <= n) {
    ++l;
  }

  for (int i = 0; i < n; ++i) {
    up[i].resize(l + 1);
  }

  up[0][0] = 0;
  Dfs(0, 0, l, tree);

  int m = 0;
  std::cin >> m;

  std::vector<int> dist = Bfs(tree, 1);

  for (int i = 0; i < m; ++i) {
    int x = 0;
    int y = 0;
    std::cin >> x >> y;
    int res = Lca(x - 1, y - 1, l);
    int len = dist[x - 1] + dist[y - 1] - 2 * dist[res];
    std::cout << len << "\n";
  }


  return 0;
}
