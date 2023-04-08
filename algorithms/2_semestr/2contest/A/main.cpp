//  83459065

#include <iostream>
#include <iterator>
#include <queue>
#include <set>
#include <vector>

using std::vector;

namespace graph {
template <typename T>
struct DefaultEdge {
  T start;
  T finish;
  T weight;
  DefaultEdge(const T& begin, const T& end, const T& weight)
      : start(begin), finish(end), weight(weight) {}
};

template <typename Vertex = int, typename Edge = DefaultEdge<Vertex>>
class IteratorGraph {
 public:
  IteratorGraph(Vertex currver, typename vector<Vertex>::iterator curriter,
                typename vector<Vertex>::iterator end)
      : current_vertex_(currver), current_(curriter), end_(end) {
    if (current_ != end_) {
      current_edge_ = {currver, *current_};
    }
  }

  IteratorGraph& operator++() {
    while (current_ != end_) {
      ++current_;
      current_edge_ = {current_, *current_};
    }
    return *this;
  }

  bool operator==(const IteratorGraph& other) const {
    return current_ == other.current_;
  }

  bool operator!=(const IteratorGraph& other) const {
    return current_ != other.current_;
  }

  IteratorGraph Begin() const { return *this; }

  IteratorGraph End() const { return {current_vertex_, end_, end_}; }

 private:
  Edge current_edge_;
  Vertex current_vertex_;
  typename vector<Vertex>::iterator current_;
  typename vector<Vertex>::iterator end_;
};

template <typename Vertex = int, typename Edge = DefaultEdge<Vertex>>
class AbstractGraph {
 public:
  using VertexType = Vertex;
  using EdgeType = Edge;

  explicit AbstractGraph(size_t vertices_num, size_t edges_num = 0)
      : vertices_number_(vertices_num), edges_number_(edges_num) {}

  size_t GetVerticesNumber() const { return vertices_number_; }
  size_t GetEdgesNumber() const { return edges_number_; }

  virtual std::vector<std::pair<Vertex, Vertex>> GetNeighbours(
      const Vertex& vertex) = 0;

 protected:
  size_t vertices_number_ = 0;
  size_t edges_number_ = 0;
};

template <typename Vertex = int, typename Edge = DefaultEdge<Vertex>>
class AdjacencyListGraph : public AbstractGraph<Vertex, Edge> {
 public:
  AdjacencyListGraph(size_t vertices_num, const std::vector<Edge>& edges)
      : AbstractGraph<Vertex, Edge>(vertices_num, edges.size()) {
    list_.resize(vertices_num);
    for (size_t edge = 0; edge < edges.size(); ++edge) {
      list_[edges[edge].start].push_back(
          {edges[edge].finish, edges[edge].weight});
      list_[edges[edge].finish].push_back(
          {edges[edge].start, edges[edge].weight});
    }
  }

  std::vector<std::pair<Vertex, Vertex>> GetNeighbours(
      const Vertex& vertex) final {
    return list_[vertex];
  }

 private:
  vector<vector<std::pair<int, int>>> list_;
};
}  // namespace graph

void Dijkstra(
    graph::AdjacencyListGraph<int, graph::DefaultEdge<int>>& graph_list,
    vector<int>& dist, int start) {
  std::set<std::pair<int, int>> queue;
  queue.insert(std::make_pair(dist[start], start));
  while (!queue.empty()) {
    int v = queue.begin()->second;
    queue.erase(queue.begin());

    std::vector<std::pair<int, int>> neighbours = graph_list.GetNeighbours(v);
    for (size_t i = 0; i < neighbours.size(); ++i) {
      int to = neighbours[i].first;
      int len = neighbours[i].second;
      if (dist[v] + len < dist[to]) {
        queue.erase(std::make_pair(dist[to], to));
        dist[to] = dist[v] + len;
        queue.insert(std::make_pair(dist[to], to));
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int app_num = 0;
  std::cin >> app_num;

  for (int k = 0; k < app_num; ++k) {
    int vertex_num = 0;
    int edges_num = 0;
    std::cin >> vertex_num >> edges_num;

    vector<graph::DefaultEdge<int>> input_edges;
    for (int i = 0; i < edges_num; ++i) {
      int start = 0;
      int finish = 0;
      int weight = 0;
      std::cin >> start >> finish >> weight;
      graph::DefaultEdge<int> input(start, finish, weight);
      input_edges.push_back(input);
    }

    graph::AdjacencyListGraph<int, graph::DefaultEdge<int>> graph(vertex_num,
                                                                  input_edges);

    int start = 0;
    const int kMax = 2009000999;
    std::cin >> start;
    vector<int> dist(vertex_num, kMax);
    dist[start] = 0;
    Dijkstra(graph, dist, start);
    for (int i = 0; i < vertex_num; ++i) {
      std::cout << dist[i] << ' ';
    }
    std::cout << std::endl;
  }

  return 0;
}