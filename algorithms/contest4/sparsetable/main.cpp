#include <iostream>
#include <vector>
#include <cmath>
using std::vector;

void BuildTable(vector<vector<std::pair<std::pair<long long, long long>, std::pair<long long, long long>>>>& sparse,  vector<long long>& input, long long tablesize) {
  /*if (input[0] < input[1]) {
    sparsetable[0][0] = std::make_pair(std::make_pair(input[0], 0), std::make_pair(input[1], 1));
  } else {
    sparsetable[0][0] = std::make_pair(std::make_pair(input[1], 1), std::make_pair(input[0], 0));
  }*/
  for (long long i = 0; i < tablesize; ++i) {
    sparse[i][0] = std::make_pair()
  }
  sparse[0] = arr;
  for (int k = 0; k + 1 < maxpow; k++) {
    for (int ind = 0; ind + (1 << k) < n; ind++) {
      sparse[k + 1][ind] = min(sparse[k][ind], sparse[k][ind + (1 << k)]);
    }
  }
}

/*vector<vector<uint64_t>> Build_Table(uint64_t a1, int n) {
  vector<vector<uint64_t>> t(std::log2(n) + 1, vector<uint64_t>(n));
  t[0][0] = a1;
  for (int i = 1; i < n; i++) {
    t[0][i] = (t[0][i - 1] * 23 + 21563) % 16714589;
  }
  for (int i = 0; i < log2(n); i++) {
    for (int j = 0; j + (2 << i) <= n; j++) {
      t[i + 1][j] = std::min(t[i][j], t[i][j + (1 << i)]);
    }
  }
  return t;
}
*/
/*uint64_t Get_Answer(int u, int v, vector<vector<uint64_t>>& t) {
  uint64_t l = log2(v - u + 1);
  return std::min(t[l][u], t[l][v - (1 << l) + 1]);
}*/

int FindMin(vector<vector<std::pair<std::pair<long long, long long>, std::pair<long long, long long>>>>& sparse, long long left, long long right) { // [l, r)
  long long power = log2(right - left);
  return min(sparse[power][left], sparse[power][right - (1 << power)]);
}



int main() {
  long long tablesize;
  long long requestsize;
  std::cin >> tablesize >> requestsize;
  vector<vector<std::pair<std::pair<long long, long long>, std::pair<long long, long long>>>> sparse
      (std::log2(tablesize) + 1,
       vector<std::pair<std::pair<long long, long long>, std::pair<long long, long long>>>(tablesize, std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0))));
  vector<long long> input;
  for (long long i = 0; i < tablesize; i++) {
    long long cinx;
    std::cin >> cinx;
    input.push_back(cinx);
  }
  BuildTable(sparse, input, tablesize);
  /*int n = 0;
int m = 0;
uint64_t a1 = 0;
std::cin >> n >> m >> a1;
vector<vector<uint64_t>> t(log2(n) + 1, vector<uint64_t>(n));
int u = 0;
int v = 0;
std::cin >> u >> v;
t = Build_Table(a1, n);
uint64_t ans = Get_Answer(std::min(u - 1, v - 1), std::max(u - 1, v - 1), t);
// std::cout << ans << std::endl;
for (int i = 1; i < m; i++) {
  u = (int)(17 * u + 751 + ans + 2 * i) % n + 1;
  v = (int)(13 * v + 593 + ans + 5 * i) % n + 1;
  ans = Get_Answer(std::min(u - 1, v - 1), std::max(u - 1, v - 1), t);
}
std::cout << u << ' ' << v << ' ' << ans << std::endl;*/
  return 0;
}