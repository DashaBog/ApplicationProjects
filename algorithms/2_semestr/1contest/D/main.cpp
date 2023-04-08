#include <iostream>
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

  virtual std::vector<Vertex> GetNeighbours(const Vertex& vertex) = 0;

 protected:
  size_t vertices_number_;
  size_t edges_number_;
};

template <typename Vertex = int, typename Edge = DefaultEdge<Vertex>>
class AdjacencyListGraph : public AbstructGraph<Vertex, Edge> {
 public:
  AdjacencyListGraph(size_t vertices_number, const std::vector<Edge>& edges)
      : AbstructGraph<Vertex, Edge>(vertices_number, edges.size()) {
    for (const auto& edge : edges) {
      list_[edge.Start()].push_back(edge.Finish());
      list_[edge.Finish()].push_back(edge.Start());
    }
    for (int i = 0; list_.size() != vertices_number; ++i) {
      if (list_.find(i) == list_.end()) {
        list_.insert({i, std::vector<Vertex>()});
      }
    }
  }

  std::vector<Vertex> GetNeighbours(const Vertex& vertex) final {
    return list_[vertex];
  }

  void DFS(int vertex, std::vector<Vertex>& component,
           std::vector<int>& visited_colors, int& cycle_start, bool& sign) {
    visited_colors[vertex] = 1;
    component.push_back(vertex);
    for (size_t i = 0; i < list_[vertex].size(); ++i) {
      int next = list_[vertex][i];
      if (visited_colors[next] == 0) {
        DFS(next, component, visited_colors, cycle_start, sign);
      }
    }
  }

  void FindCycle(size_t vertex_num) {
    std::vector<int> visited_colors(vertex_num + 2, 0);
    std::vector<std::vector<Vertex>> components;
    int cycle_start = -1;
    for (size_t i = 1; i <= vertex_num; ++i) {
      bool sign = true;
      std::vector<Vertex> component;
      if (visited_colors[i] == 0) {
        DFS(i, component, visited_colors, cycle_start, sign);
        components.push_back(component);
      }
    }

    std::cout << components.size() << "\n";
    for (size_t i = 0; i < components.size(); ++i) {
      std::cout << components[i].size() << "\n";
      for (size_t j = 0; j < components[i].size(); ++j) {
        std::cout << components[i][j] << " ";
      }
      std::cout << "\n";
    }
  }

 private:
  std::unordered_map<Vertex, std::vector<Vertex>> list_;
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

  list_graph.FindCycle(vertex_num);

  return 0;
}