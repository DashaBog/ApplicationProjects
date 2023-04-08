#include <algorithm>
#include <iostream>
#include <vector>

using std::vector, std::cin, std::cout;

class test {
 public:
  test(size_t sizet, size_t numt) : vertexnum_(sizet), edgenum_(numt) {
    log_ = std::__lg(vertexnum_);
    dp_.assign(vertexnum_, std::vector<int64_t>(log_ + 1));
    h_.assign(vertexnum_, 0);
    t_out.resize(vertexnum_);
    t_in.resize(vertexnum_);
    list_.resize(vertexnum_);
    for (int64_t i = 1; i < vertexnum_; i++) {
      int64_t num;
      std::cin >> num;
      list_[num].push_back(i);
      list_[i].push_back(num);
    }
  }

  int64_t Filling(int64_t start, int64_t finish) {
    if (h_[start] < h_[finish]) {
      std::swap(start, finish);
    }
    int diff = h_[start] - h_[finish];
    for (int64_t i = log_ - 1; i >= 0; --i) {
      int64_t bin = 1 << i;
      if (bin <= diff) {
        start = dp_[start][i];
        diff -= bin;
      }
    }

    if (start != finish) {
      for (int64_t i = log_ - 1; i >= 0; --i) {
        if (dp_[start][i] != dp_[finish][i]) {
          start = dp_[start][i];
          finish = dp_[finish][i];
        }
      }
      return dp_[start][0];
    }
    return start;
  }

  template<class T = int64_t>
  struct Query {
    T x;
    T y;
    T z;
  };

  void DFS(int64_t first, int64_t second) {
    dp_[first][0] = second;
    h_[first] = h_[second] + 1;
    t_in[first] = ++timer_;
    for (int64_t i = 0; i < log_; ++i) {
      dp_[first][i + 1] = dp_[dp_[first][i]][i];
    }
    for (size_t i = 0; i < list_[first].size(); ++i) {
      if (list_[first][i] != second) {
        DFS(list_[first][i], first);
      }
    }
    t_out[first] = ++timer_;
  }

  void Count() {
    int64_t first, second;
    Query<int64_t> te;
    std::cin >> first >> second;
    std::cin >> te.x >> te.y >> te.z;
    int64_t sum_ = 0;
    sum_ += Filling(first, second);
    int64_t prev = sum_;
    int64_t ans;
    for(int64_t i = 1; i < edgenum_; ++i) {
      first = (te.x * first + te.y * second + te.z) % vertexnum_;
      second = (te.x * second + te.y * first + te.z) % vertexnum_;
      int64_t elem = (first + prev) % vertexnum_;
      ans = Filling(elem, second);
      sum_ += ans;
      prev = ans;
    }
    std::cout << sum_ << std::endl;
  }

 private:
  int64_t vertexnum_;
  int64_t edgenum_;
  std::vector<std::vector<int64_t>> list_;
  std::vector<std::vector<int64_t>> dp_;
  int64_t timer_;
  std::vector<int64_t> t_out, t_in;
  std::vector<int64_t> h_;
  int64_t log_;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  size_t vertex_num, query_num;
  std::cin >> vertex_num >> query_num;
  test Solution(vertex_num, query_num);

  Solution.DFS(0, 0);
  Solution.Count();
}