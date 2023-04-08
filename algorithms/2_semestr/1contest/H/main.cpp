#include <algorithm>
#include <iostream>
#include <set>
#include <stack>
#include <unordered_map>
#include <vector>

namespace graph {
template <typename T>
struct DefaultEdge : std::pair<T, T> {
  using BaseClass = std::pair<T, T>;
  DefaultEdge(const T& first, const T& second) : BaseClass(first, second) {}
  const T& Start() const { return BaseClass::first; };
  const T& Finish() const { return BaseClass::second; };
};

template <typename Vertex = int, typename Edge = DefaultEdge<Vertex>>
class AbstructGraph {
 public:
  using VertexType = Vertex;
  using EdgeType = DefaultEdge<Vertex>;

  explicit AbstructGraph(size_t vertices_number, size_t edges_number = 0)
      : vertices_number_(vertices_number), edges_number_(edges_number) {}

  size_t GetVertexNumber() { return vertices_number_; }
  size_t GetEdgeNumber() { return edges_number_; }

 protected:
  size_t vertices_number_;
  size_t edges_number_;
};

template <typename Vertex = int, typename Edge = DefaultEdge<Vertex>>
class AdjacencyListGraph : public AbstructGraph<Vertex, Edge> {
 public:
  AdjacencyListGraph(size_t vertices_number, const std::vector<Edge>& edges)
      : AbstructGraph<Vertex, Edge>(vertices_number, edges.size()) {
    for (size_t edge = 0; edge < edges.size(); ++edge) {
      list_[edges[edge].Start()].push_back({edges[edge].Finish(), edge});
      list_[edges[edge].Finish()].push_back({edges[edge].Start(), edge});
    }
  }

  void DfsBridges(int vertex, int p, std::vector<Vertex>& used, int& timer,
                  std::set<Vertex>& briges) {
    used[vertex] = 1;
    tin_[vertex] = timer;
    ret_[vertex] = timer;
    ++timer;
    int children = 0;
    for (size_t i = 0; i < list_[vertex].size(); ++i) {
      int to = list_[vertex][i].first;
      if (to == p) {
        continue;
      }
      if (used[to] == 1) {
        ret_[vertex] = std::min(ret_[vertex], tin_[to]);
      } else {
        DfsBridges(to, vertex, used, timer, briges);
        ret_[vertex] = std::min(ret_[vertex], ret_[to]);
        if (ret_[to] >= tin_[vertex] && (p != -1)) {
          briges.insert(vertex);
        }
        ++children;
      }
    }
    if (p == -1 && children > 1) {
      briges.insert(vertex);
    }
  }

  void Solution(size_t vertex_num) {
    std::vector<int> used(vertex_num + 1, 0);
    std::set<Vertex> briges;
    tin_.assign(vertex_num + 1, 0);
    ret_.assign(vertex_num + 1, 0);
    int timer = 0;

    for (size_t i = 1; i <= vertex_num; ++i) {
      if (used[i] == 0) {
        DfsBridges(i, -1, used, timer, briges);
      }
    }

    std::cout << briges.size() << "\n";
    for (auto& bridge : briges) {
      std::cout << bridge << "\n";
    }
  }

 private:
  std::unordered_map<Vertex, std::vector<std::pair<Vertex, Vertex>>> list_;
  std::vector<Vertex> tin_;
  std::vector<Vertex> ret_;
};
}  // namespace graph

int main() {
  size_t vertex_num = 0;
  size_t edges_num = 0;

  std::cin >> vertex_num >> edges_num;
  std::vector<graph::DefaultEdge<int>> edges;
  for (size_t i = 0; i < edges_num; ++i) {
    int edge_start;
    int edge_finish;
    std::cin >> edge_start >> edge_finish;
    edges.push_back(graph::DefaultEdge(edge_start, edge_finish));
  }

  graph::AdjacencyListGraph<int, graph::DefaultEdge<int>> list_graph(vertex_num,
                                                                     edges);

  list_graph.Solution(vertex_num);

  return 0;
}