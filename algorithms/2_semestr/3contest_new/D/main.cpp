#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using std::vector, std::pair, std::string;

class Solution {
 public:

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

  void Kruskala() {
    int64_t cost = 0;
    vector<pair<int64_t, int64_t>> minost;

    sort(list_edges.begin(), list_edges.end());
    for (int j = 0; j < vertex_num_; ++j) {
      MakeSet(j);
    }

    for (auto i = 0; i < list_edges.size(); ++i) {
      int64_t begin = list_edges[i].second.first;
      int64_t end = list_edges[i].second.second;
      int64_t l = list_edges[i].first;
      if (FindSet(begin) != FindSet(end)) {
        cost += l;
        minost.push_back(list_edges[i].second);
        UnionSets(begin, end);
      }
    }

    std::cout << cost;
  }

  void Input() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> vertex_num_;
    vertex_num_++;
    matrix.resize(vertex_num_, vector<int64_t> (vertex_num_));
    parent.resize(vertex_num_);
    rank.resize(vertex_num_);
    for (int i = 0; i < vertex_num_ - 1; ++i) {
      for (int j = 0; j < vertex_num_ - 1; ++j) {
        int64_t weight;
        std::cin >> weight;
        matrix[i][j] = weight;
        list_edges.emplace_back(weight, std::make_pair(i, j));
      }
    }

    for (int i = 0; i < vertex_num_ - 1; ++i) {
      int64_t weight;
      std::cin >> weight;
      matrix[vertex_num_ - 1][i] = weight;
      matrix[i][vertex_num_ - 1] = weight;
      list_edges.emplace_back(weight, std::make_pair(i, vertex_num_ - 1));
      list_edges.emplace_back(weight, std::make_pair(vertex_num_ - 1, i));
    }

    Kruskala();
  }

 private:
  size_t vertex_num_;
  size_t edge_num_;
  vector<std::pair<int64_t, std::pair<int64_t, int64_t>>> list_edges;
  vector<vector<int64_t>> matrix;

  vector<int64_t> parent;
  vector<int64_t> rank;
  vector<string> answers;
};

int main() {
  Solution test;
  test.Input();
  return 0;
}