#include <iostream>
#include <iterator>
#include <vector>
#include <string>

using std::vector, std::pair, std::string;

class Solution {
 public:
  struct Query {
    string qustr;
    int64_t begin;
    int64_t end;
  };

  Solution() : vertex_num_(1), edge_num_(0) {
    list_.resize(1);
  }

  void MakeSet(int64_t v) {
    parent[v] = v;
    rank[v] = 0;
  }

  int64_t FindSet(int64_t v) {
    if (v == parent[v])
      return v;
    return parent[v] = FindSet(parent[v]);
  }

  void UnionSets(int64_t a, int64_t b) {
    a = FindSet(a);
    b = FindSet(b);
    if (a != b) {
      if (rank[a] < rank[b])
        std::swap (a, b);
      parent[b] = a;
      if (rank[a] == rank[b])
        ++rank[a];
    }
  }

  void Cut(int64_t begin, int64_t end) {
    UnionSets(begin, end);
  }

  void Ask(int64_t begin, int64_t end) {
    int64_t first_set = FindSet(begin);
    int64_t second_set = FindSet(end);
    if (first_set == second_set) {
      answers.emplace_back("YES\n");
    } else {
      answers.emplace_back("NO\n");
    }
  }

  void Input() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t query_num;
    std::cin >> vertex_num_ >> edge_num_ >> query_num;
    list_.resize(vertex_num_ + 1);
    parent.resize(vertex_num_ + 1);
    rank.resize(vertex_num_ + 1);
    for (int i = 0; i < vertex_num_ + 1; ++i) {
      MakeSet(i);
    }
    for (int i = 0; i < edge_num_; ++i) {
      int64_t begin, end;
      std::cin >> begin >> end;
      list_[begin].push_back(end);
      list_[end].push_back(begin);
    }
    for (size_t i = 0; i < query_num; ++i) {
      Query in;
      std::cin >> in.qustr;
      std::cin >> in.begin >> in.end;
      queries.push_back(in);
    }

    for (auto iter = queries.rbegin(); iter != queries.rend(); ++iter) {
      if (iter->qustr == "cut") {
        Cut(iter->begin, iter->end);
      } else {
        Ask(iter->begin, iter->end);
      }
    }

    for (auto iter = answers.rbegin(); iter != answers.rend(); ++iter) {
      std::cout << *iter;
    }
  }

 private:
  size_t vertex_num_;
  size_t edge_num_;
  vector<vector<int64_t>> list_;

  vector<int64_t> parent;
  vector<int64_t> rank;
  vector<Query> queries;
  vector<string> answers;
};

int main() {
  Solution test;
  test.Input();
  return 0;
}