#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

using std::vector, std::cin, std::cout, std::pair;

class Solution {
 public:
  int64_t Search(int64_t& value) {
    int64_t temp = value;
    while (temp != ansces_[temp]) {
      temp = ansces_[temp];
    }

    while(value != temp) {
      size_t p = ansces_[value];
      ansces_[value] = temp;
      value = p;
    }
    return temp;
  }

  void Process() {
    int64_t weight = 0;
    std::sort(list_.begin(), list_.end());
    for (size_t i = 0; i < edge_num_; ++i) {
      pair<int64_t, int64_t> edge = list_[i].second;
      if (Search(edge.first) != Search(edge.second)) {
        weight += list_[i].first;
        minost_[edge.second].emplace_back(-list_[i].first, edge.first);
        minost_[edge.first].emplace_back(-list_[i].first, edge.second);

        int64_t first = Search(edge.first);
        int64_t second = Search(edge.second);
        if (first != second) {
          ansces_[first] = second;
        }
      }
    }
  }

  int Diving(int64_t beg, int64_t end, int64_t val) {
    if (beg == end) {
      return val;
    }
    int64_t res = 0;
      used_[beg] = true;
      for (size_t i = 0; i < minost_[beg].size(); ++i) {
        if (!used_[minost_[beg][i].second]) {
          res = Diving(minost_[beg][i].second, end, std::min(val, minost_[beg][i].first));
          if (res > 0) {
            return std::min(res, val);
          }
        }
      }
      return res;
  }

  Solution(int64_t num_v, int64_t num_edge, int64_t num_req) : vertex_num_(num_v), edge_num_(num_edge), requests_num_(num_req) {
    minost_.resize(num_v);
    used_.resize(num_v, false);
    ansces_.resize(num_v + 1, 0);
    power_.resize(num_v + 1, 0);

    for (size_t i = 0; i <= num_v; ++i) {
      power_[i] = 0;
      ansces_[i] = i;
    }

    for (size_t i = 0; i < num_edge; ++i) {
      int64_t start, finish, weight;
      cin >> start >> finish >> weight;
      list_.push_back({-weight, {--start, --finish}});
    }
  }

  void Output() {
    for (size_t i = 0; i < requests_num_; i++) {
      int64_t start, finish;
      cin >> start >> finish;
      used_.assign(vertex_num_, false);
      cout << Diving(--start, --finish, std::numeric_limits<int64_t>::max()) << "\n";
     }
  }

 private:
  int64_t vertex_num_;
  int64_t edge_num_;
  int64_t requests_num_;
  vector<int64_t> ansces_;
  vector<int64_t> power_;
  vector<bool> used_;
  vector<vector<pair<int64_t, int64_t>>> minost_;
  vector<pair<int64_t, pair<int64_t, int64_t>>> list_;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int64_t vertex, edge, req;
  std::cin >> vertex;
  std::cin >> edge;
  std::cin >> req;

  Solution test(vertex, edge, req);
  test.Process();
  test.Output();
  return 0;
}