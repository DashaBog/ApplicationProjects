#include <iostream>
#include <unordered_map>

template <typename T>
struct DefaultEdge {
  T start;
  T finish;
  T weight;
  DefaultEdge(const T& begin, const T& end, const T& weight)
      : start(begin), finish(end), weight(weight) {}
};

template<typename Vertex>
class DSU {
  struct Edge {
    Vertex parent;
    Vertex rank;
    int64_t friendly;
  };

 public:
  DSU(Vertex vertex_num) {
    for (int i = 0; i < vertex_num + 1; ++i) {
      map_.insert({i, {i, 0, 0}});
    }
  }

  Vertex FindSet(Vertex v) {
    if (v == map_[v].parent)
      return v;
    return map_[v].parent = FindSet(map_[v].parent);
  }

  void UnionSets(Vertex a, Vertex b, int64_t weight) {
    a = FindSet(a);
    b = FindSet(b);
    if (a != b) {
      if (map_[a].rank < map_[b].rank) {
        std::swap(a, b);
      }
      map_[b].parent = a;
      map_[a].friendly += map_[b].friendly;
      if (map_[a].rank == map_[b].rank)
        ++map_[a].rank;
    }
    map_[a].friendly += weight;
  }

  void InputQuery(size_t query_num) {
    for (int i = 0; i < query_num; ++i) {
      int def;
      std::cin >> def;
      if (def == 1) {
        int64_t begin, end, weight;
        std::cin >> begin >> end >> weight;
        UnionSets(begin, end, weight);
      } else if (def == 2) {
        int64_t vertex;
        std::cin >> vertex;
        std::cout << map_[FindSet(vertex)].friendly << "\n";
      }
    }
  }

 private:
  std::unordered_map<Vertex, Edge> map_;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  size_t vertex_num;
  size_t query_num;
  std::cin >> vertex_num >> query_num;

  DSU<int64_t> test(vertex_num);
  test.InputQuery(query_num);
  return 0;
}