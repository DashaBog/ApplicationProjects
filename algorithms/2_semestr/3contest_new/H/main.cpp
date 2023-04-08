#include <iostream>
#include <vector>
#include <string>

using std::vector, std::pair, std::string;

class Solution {
 public:
  struct Query {
    int64_t begin;
    int64_t end;
  };

  Solution() : vertex_num_(1), edge_num_(0), timer_(0), upglobal_(1) {
    list_.resize(1);
  }

  void DFS(int64_t vertex, int64_t anses = 1) {
    tin_[vertex] = ++timer_;
    upper_[vertex][0] = anses;
    for (int64_t i = 1; i <= upglobal_; ++i) {
      upper_[vertex][i] = upper_[upper_[vertex][i - 1]][i - 1];
    }
    for (size_t i = 1; i <= list_[vertex].size(); ++i) {
      int64_t to = list_[vertex][i];
      if (to != anses) {
        DFS(to, vertex);
      }
    }
    tout_[vertex] = ++timer_;
  }

  bool upper(int64_t begin, int64_t end) {
    return tin_[begin] <= tin_[end] && tout_[begin] >= tout_[end];
  }

  int64_t LCA(int64_t begin, int64_t end) {
    /*if (begin > vertex_num_ || end > vertex_num_ || begin < 1 || end < 1) {
      return 0;
    }*/
    if (upper(begin, end)) {
      return begin;
    }
    if (upper(end, begin)) {
      return end;
    }
    for (int64_t i = upglobal_; i >= 0; --i) {
      if (!upper(upper_[begin][i], end)) {
        begin = upper_[begin][i];
      }
    }
    return upper_[begin][0];
  }

  void Input() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t query_num;
    std::cin >> vertex_num_;
    edge_num_ = vertex_num_ - 1;
    list_.resize(vertex_num_ + 1);
    tin_.resize(vertex_num_ + 1);
    tout_.resize(vertex_num_ + 1);
    upper_.resize(vertex_num_ + 1);

    parent_.resize(vertex_num_ + 1);
    depth_.resize(vertex_num_ + 1);

    for (int i = 0; i < edge_num_; ++i) {
      int64_t begin, end;
      std::cin >> begin >> end;
      list_[begin].push_back(end);
      list_[end].push_back(begin);
    }

    for (int64_t up = 1; (1 << up) <= vertex_num_; ++up, upglobal_ = up) {}

    for (size_t i = 0; i <= vertex_num_; ++i) {
      upper_[i].resize(upglobal_ + 1, 0);
    }

    DFS(1);

    std::cin >> query_num;
    for (size_t i = 0; i < query_num; ++i) {
      Query in;
      std::cin >> in.begin >> in.end;
            std::cout << depth_[in.begin] + depth_[in.end] - depth_[LCA(in.begin, in.end)] << "\n";
      
    }
  }

 private:
  size_t vertex_num_;
  size_t edge_num_;
  vector<vector<int64_t>> list_;

  vector<vector<int64_t>> upper_;
  vector<int64_t> tin_, tout_;
  int64_t upglobal_;
  int64_t timer_;

  vector<int64_t> parent_;
  vector<int64_t> depth_;
};

int main() {
  Solution test;
  test.Input();
  return 0;
}