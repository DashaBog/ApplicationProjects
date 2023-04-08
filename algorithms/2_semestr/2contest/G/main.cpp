#include <iostream>
#include <vector>

using std::vector;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  std::cin >> n;

  vector<vector<int>> g(n, vector<int>(n));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int w = 0;
      std::cin >> w;
      g[i][j] = w;
    }
  }

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if ((g[i][k] != 0) && (g[k][j] != 0)) {
          g[i][j] = 1;
        }
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << g[i][j] << ' ';
    }
    std::cout << std::endl;
  }
  return 0;
}