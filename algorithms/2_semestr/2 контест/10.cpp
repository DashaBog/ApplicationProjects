#include <iostream>
#include <vector>

using std::vector;

void MakeSet (int v, std::vector<int> &parent) {
  parent[v] = v;
}

int FindSet(int v, std::vector<int> &parent) {
  if (v == parent[v]){
    return v;
  }
  return parent[v] = FindSet(parent[v], parent);
}

void UnionSet(int x, int y, std::vector<int> &parent, std::vector<int>& weight) {
  x = FindSet(x, parent);
  y = FindSet(y, parent);
  if (x != y) {
    parent[x] = y;
    weight[y] += weight[x];
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  std::vector<int> weight(n);
  std::vector<int> parent(n);

  for (int i = 0; i < n; ++i) {
    MakeSet(i, parent);
  }

  for (int i = 0; i < m; ++i) {
    int command = 0;
    std::cin >> command;
    if (command == 1) {
      int x = 0;
      int y = 0;
      int w = 0;
      std::cin >> x >> y >> w;
      if (FindSet(x - 1, parent) != FindSet(y - 1, parent)) {
        UnionSet(x - 1, y - 1, parent, weight);
      }
      weight[FindSet(x - 1, parent)] += w;
    } else {
      int x = 0;
      std::cin >> x;
      std::cout << weight[FindSet(x - 1, parent)] << "\n";
    }
  }
  return 0;
}
