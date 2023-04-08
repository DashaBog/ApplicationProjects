#include <iostream>
#include <vector>
#include <queue>

using std::vector;

vector<long long> tin, tout;
long long timer;
vector <vector<long long>> up;

void Dfs(long long v, long long p, long long l, std::vector<std::vector<long long>>& g) {
  tin[v] = ++timer;
  up[v][0] = p;
  for (long long i = 1; i <= l; ++i) {
    up[v][i] = up[up[v][i - 1]][i - 1];
  }
  for (size_t i = 0; i < g[v].size(); ++i) {
    long long to = g[v][i];
    if (to != p) {
      Dfs(to, v, l, g);
    }
  }
  tout[v] = ++timer;
}

bool Upper(long long a, long long b) {
  return tin[a] <= tin[b] && tout[a] >= tout[b];
}

long long Lca(long long a, long long b, long long l) {
  if (Upper(a, b)) {
    return a;
  }
  if (Upper(b, a)) {
    return b;
  }
  for (long long i = l; i >= 0; --i) {
    if (!Upper(up[a][i], b)) {
      a = up[a][i];
    }
  }
  return up[a][0];
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  long long n = 0;
  long long m = 0;
  std::cin >> n >> m;

  std::vector<std::vector<long long>> tree(n);

  for (long long i = 0; i < n - 1; ++i) {
    long long x = 0;
    std::cin >> x;
    tree[x].emplace_back(i + 1);
  }

  long long a1 = 0;
  long long a2 = 0;
  std::cin >> a1 >> a2;
  long long x = 0;
  long long y = 0;
  long long z = 0;
  std::cin >> x >> y >> z;

  tin.resize(n), tout.resize(n), up.resize(n);

  long long l = 1;
  while ((1 << l) <= n) {
    ++l;
  }

  for (long long i = 0; i < n; ++i) {
    up[i].resize(l + 1);
  }

  up[0][0] = 0;
  Dfs(0, 0, l, tree);

  long long sum = 0;
  vector<long long> a(2 * m + 1);

  a[1] = a1;
  a[2] = a2;
  for (long long i = 3; i < 2*m + 1; ++i) {
    a[i] = (x * a[i - 2] + y * a[i - 1] + z) % n;
  }

  long long res = 0;
  for (long long i = 1; i <= m; ++i) {
    res = Lca(a1, a2, l);
    sum += res;
    if (i == m) {
      break;
    }
    a1 = (a[2 * (i + 1) - 1] + res) % n;
    a2 = a[2 * (i + 1)];
  }

  std::cout << sum << std::endl;

  return 0;
}
