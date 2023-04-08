#include <iostream>
#include <vector>
#include <map>

using std::vector, std::pair, std::map;
const int kInf = -100000000;
void GetShortestPath(int a, int b, vector<vector<int>>& next, vector<int>& res, map<pair<int, int>, int>& flights){
  int first = a, second = next[first][b];
  while (first != b) {
    res.push_back(flights[std::make_pair(first, second)]);
    first = second, second = next[first][b];
  }
}

bool floyd(vector<vector<int>>& g, vector<int>& a, vector<int>& res, vector<vector<int>>& next, map<pair<int, int>, int>& flights){
  size_t n = g.size();
  for (size_t k = 0; k < n; ++k)
    for (size_t i = 0; i < n; ++i)
      for (size_t j = 0; j < n; ++j)
        if (g[i][k] > INF && g[k][j] > INF) {
          if (g[i][j] < g[i][k] + g[k][j]) {
            g[i][j] = g[i][k] + g[k][j];
            next[i][j] = next[i][k];
          }
        }

  for (size_t i = 0; i < a.size() - 1; ++i){
    for (size_t j = 0; j < n; ++j){
      if (g[a[i]][j] > INF && g[j][j] > 0 && g[j][a[i + 1]] > INF){
        return false;
      }
    }
  }
  for (size_t i = 0; i < a.size() - 1; ++i){
    GetShortestPath(a[i], a[i + 1], next, res, flights);
  }
  return true;
}

int main() {
  int n, m, k;
  std::cin >> n >> m >> k;
  vector<vector<int>> g(n, vector<int>(n, INF));
  vector<int> a(k);
  vector<vector<int>> next(n, vector<int>(n, -1));
  vector<int> res;
  map<pair<int, int>, int> flights;
  for (int i = 0; i < m; ++i){
    int b, e, w;
    std::cin >> b >> e >> w;
    g[b - 1][e - 1] = w;
    next[b - 1][e - 1] = e - 1;
    flights.insert({std::make_pair(b - 1, e - 1), i});
  }

  for (int i = 0; i < n; ++i){
    g[i][i] = 0;
    next[i][i] = i;
  }

  for (int i = 0; i < k; ++i){
    std::cin>>a[i];
    --a[i];
  }
  if (!floyd(g, a, res, next, flights)){
    std::cout << "infinitely kind";
  }
  else{
    std::cout << res.size() << '\n';
    for (int item : res){
      std::cout << item + 1 << ' ';
    }
  }
  return 0;
}
