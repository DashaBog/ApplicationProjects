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

void UnionSet(int x, int y, std::vector<int> &parent) {
  x = FindSet(x, parent);
  y = FindSet(y, parent);
  if (x != y) {
    parent[x] = y;
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  int m = 0;
  int k = 0;
  std::cin >> n >> m >> k;

  std::vector<std::vector<int>> g(n);

  for (int i = 0; i < m; ++i) {
    int x = 0;
    int y = 0;
    std::cin >> x >> y;
    g[x - 1].emplace_back(y - 1);
    g[y - 1].emplace_back(x - 1);
  }

  std::vector<std::pair<int, std::pair<int, int>>> commands;

  for (int i = 0; i < k; ++i) {
    std::string command;
    std::cin >> command;
    int x = 0;
    int y = 0;
    std::cin >> x >> y;
    std::pair<int, int> e = std::make_pair(x - 1, y - 1);
    if (command == "ask") {
      commands.emplace_back(1, e);
    } else {
      commands.emplace_back(0, e);
    }
  }

  std::vector<int> parent(n);

  for (int i = 0; i < n; ++i) {
    MakeSet(i,parent);
  }

  std::vector<int> res(k);

  for (int i = k - 1; i >= 0; i--) {
    if (commands[i].first == 1) {
      res[i] = (FindSet(commands[i].second.first, parent) == FindSet(commands[i].second.second, parent));
    }
    else {
      UnionSet(commands[i].second.first, commands[i].second.second, parent);
    }
  }

  for (int i = 0; i < k; ++i) {
    if (commands[i].first == 1) {
      if (res[i]) {
        std::cout << "YES" << "\n";
      } else {
        std::cout << "NO" << "\n";
      }
    }
  }

  return 0;
}
