#include <iostream>
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
      translist_[edge.Finish()].push_back(edge.Start());
    }
  }

  std::vector<Vertex> GetNeighbours(const Vertex& vertex) final {
    return list_[vertex];
  }

  void DfsDirect(int vertex, std::vector<int>& used,
                 std::vector<Vertex>& order) {
    used[vertex] = 1;
    for (size_t i = 0; i < list_[vertex].size(); ++i) {
      if (used[list_[vertex][i]] == 0) {
        DfsDirect(list_[vertex][i], used, order);
      }
    }
    order.push_back(vertex);
  }

  void DfsIndirect(int vertex, std::vector<int>& used,
                   std::vector<Vertex>& component) {
    used[vertex] = 1;
    component.push_back(vertex);
    for (size_t i = 0; i < translist_[vertex].size(); ++i) {
      if (used[translist_[vertex][i]] == 0) {
        DfsIndirect(translist_[vertex][i], used, component);
      }
    }
  }

  void Solution(size_t vertex_num) {
    std::vector<int> used_direct(vertex_num + 2, 0);
    std::vector<int> used_indirect(vertex_num + 2, 0);
    std::vector<Vertex> order, component;

    for (size_t i = 1; i <= vertex_num; ++i) {
      if (used_direct[i] == 0) {
        DfsDirect(i, used_direct, order);
      }
    }

    int components_num = 0;
    std::vector<int> component_vertex(vertex_num + 1, 0);
    for (size_t i = 1; i <= vertex_num; ++i) {
      int vertex = order[vertex_num - i];
      if (used_indirect[vertex] == 0) {
        DfsIndirect(vertex, used_indirect, component);
        components_num++;
        for (size_t j = 0; j < component.size(); ++j) {
          component_vertex[component[j]] = components_num;
        }
        component.clear();
      }
    }

    std::cout << components_num << "\n";
    for (size_t j = 1; j < component_vertex.size(); ++j) {
      std::cout << component_vertex[j] << " ";
    }
  }

 private:
  std::unordered_map<Vertex, std::vector<Vertex>> list_;
  std::unordered_map<Vertex, std::vector<Vertex>> translist_;
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