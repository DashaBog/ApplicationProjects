#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

namespace graph {
template<typename T>
struct DefaultEdge : std::pair<T, T> {
  using BaseClass = std::pair<T, T>;
  DefaultEdge(const T& first, const T& second) : BaseClass(first, second) {}
  const T& Start() const { return BaseClass::first; };
  const T& Finish() const { return BaseClass::second; };
};

template<typename Vertex = int, typename Edge = DefaultEdge<Vertex>>
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

template<typename Vertex = int, typename Edge = DefaultEdge<Vertex>>
class AdjacencyListGraph : public AbstructGraph<Vertex, Edge> {
 public:
  AdjacencyListGraph(size_t vertices_number, const std::vector<std::pair<Edge, int>>& edges)
      : AbstructGraph<Vertex, Edge>(vertices_number, edges.size()) {
    for (const auto& edge : edges) {
      list_[edge.first.Start()].push_back({edge.first.Finish(), edge.second});
    }
  }

  void BFS(int start, int finish, int vertex_num) {
    const int max = 31;

    std::vector<std::vector<Vertex>> q(31, std::vector<Vertex>());
    q[0].push_back(start);
    std::vector<bool> used(vertex_num, false);
    std::unordered_map<Vertex, int> dest;
    dest.insert({start, 0});

    for (int x = 0; x < max * vertex_num; ++x) {
      while (!q[x % 31].empty()) {
        Vertex v = q[x % 31].back();
        q[x % 31].pop_back();
        if (!used[v]) {
          used[v] = true;
          for (size_t i = 0; i < list_[v].size(); ++i) {
            Vertex to = list_[v][i].first;
            if (used[to]) {
              dest[to] = std::min(dest[to], dest[v] + list_[v][i].second);
            } else {
              if (dest[to] == 0) {
                dest[to] = dest[v] + list_[v][i].second;
              } else {
                dest[to] = std::min(dest[to], dest[v] + list_[v][i].second);
              }
            }
            q[dest[to] % 31].push_back(to);
          }
        }
      }
    }

    if (!used[finish])
      std::cout << "-1";
    else {
      std::cout << dest[finish];
    }

  }

 private:
  std::unordered_map<Vertex, std::vector<std::pair<Vertex, int>>> list_;
};
}  // namespace graph

int main() {
  size_t vertex_num = 0;
  size_t edges_num = 0;
  int start = 0, finish = 0;

  std::cin >> vertex_num >> edges_num;
  std::cin >> start >> finish;
  std::vector<std::pair<graph::DefaultEdge<int>, int>> edges;
  for (size_t i = 0; i < edges_num; ++i) {
    int edge_start;
    int edge_finish;
    int weight;
    std::cin >> edge_start >> edge_finish >> weight;
    edges.push_back({graph::DefaultEdge(edge_start, edge_finish), weight});
  }

  graph::AdjacencyListGraph<int, graph::DefaultEdge<int>> list_graph(vertex_num,
                                                                     edges);

  list_graph.BFS(start, finish, vertex_num);

  return 0;
}
