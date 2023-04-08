#include <algorithm>
#include <iostream>
#include <iterator>
#include <queue>
#include <limits>
#include <set>
#include <vector>
#include <unordered_map>

using std::vector, std::pair, std::set;

namespace graph {

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
      MakeSet(i);
    }
  }

  DSU() = default;

  void MakeSet(int64_t v) {
    map_.insert({v, {v, 0, 0}});
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

 private:
  std::unordered_map<Vertex, Edge> map_;
};

template <typename T>
struct DefaultEdge {
  T weight;
  T start;
  T finish;
  DefaultEdge(const T& begin, const T& end, const T& weight)
      : start(begin), finish(end), weight(weight) {}
};

template <typename Vertex = int64_t, typename Edge = DefaultEdge<Vertex>>
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

template <typename Vertex = int64_t, typename Edge = DefaultEdge<Vertex>>
class AbstractGraph {
 public:
  using VertexType = Vertex;
  using EdgeType = Edge;

  explicit AbstractGraph(size_t vertices_num, size_t edges_num = 0)
      : vertices_number_(vertices_num), edges_number_(edges_num) {}

  size_t GetVerticesNumber() const { return vertices_number_; }
  size_t GetEdgesNumber() const { return edges_number_; }

  virtual std::vector<std::pair<Vertex, Vertex>> GetNeighbours(const Vertex& vertex) = 0;

 protected:
  size_t vertices_number_ = 0;
  size_t edges_number_ = 0;
};

template <typename Vertex = int64_t, typename Edge = DefaultEdge<Vertex>>
class AdjacencyListGraph : public AbstractGraph<Vertex, Edge> {
 public:
  AdjacencyListGraph(size_t vertices_num, const std::vector<Edge>& edges)
      : AbstractGraph<Vertex, Edge>(vertices_num, edges.size()) {
    list_.resize(vertices_num + 1);
    list_edges_.resize(edges.size());
    for (size_t edge = 0; edge < edges.size(); ++edge) {
      list_[edges[edge].start].push_back(
          {edges[edge].finish, edges[edge].weight});
      list_[edges[edge].finish].push_back(
          {edges[edge].start, edges[edge].weight});
      list_edges_[edge] = {edges[edge].weight, {edges[edge].start, edges[edge].finish}};
    }
  }

  std::vector<std::pair<Vertex, Vertex>> GetNeighbours(
      const Vertex& vertex) final {
    return list_[vertex];
  }

  vector<std::pair<int64_t, std::pair<int64_t, int64_t>>>& SetEdges() {
    return list_edges_;
  }

 private:
  vector<vector<std::pair<int64_t, int64_t>>> list_;
  vector<std::pair<int64_t, std::pair<int64_t, int64_t>>> list_edges_;
};

template <typename Vertex = int64_t, typename Edge = DefaultEdge<Vertex>>
class TreeGraph : public AbstractGraph<Vertex, Edge> {
 public:
  TreeGraph(size_t vertex_num, vector<pair<int64_t, pair<Vertex, Vertex>>>& minost) :
            AbstractGraph<Vertex, Edge>(vertex_num, minost.size()) {
    for (int i = 0; i < minost.size(); ++i) {
      tree_.push_back({minost[i].first, minost[i].second});
    }
  }

  std::vector<std::pair<Vertex, Vertex>> GetNeighbours(const Vertex& vertex) final {
    std::vector<std::pair<Vertex, Vertex>> list_;
    for (int i = 0; i < tree_.size(); ++i) {
      if (tree_[i].second.first == vertex) {
        list_.push_back({tree_[i].first, tree_[i].second.second});
      }
    }
    return list_;
  }

 private:
  vector<pair<int64_t, pair<Vertex, Vertex>>> tree_;
};

template <typename Vertex = int64_t, typename Edge = DefaultEdge<Vertex>>
/*TreeGraph<Vertex, Edge>*/ void Prima(AdjacencyListGraph<Vertex, Edge> test) {
  const int64_t kInt64 = std::numeric_limits<int64_t>::max();

  std::set<std::pair<int, int>> queue;
  queue.insert(std::make_pair(dist[start], start));
  while (!queue.empty()) {
    int v = queue.begin()->second;
    queue.erase(queue.begin());

    std::vector<std::pair<int, int>> neighbours = test.GetNeighbours(v);
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
  /*vector<Vertex> minostov (test.GetVerticesNumber(), kInt64), sel_e(test.GetVerticesNumber(), -1);
  minostov[0] = 0;
  set<pair<Vertex, Vertex>> used;
  used.insert ({0, 0});
  for (int i = 0; i < test.GetVerticesNumber(); ++i) {
    if (!used.empty()) {
      int v = used.begin()->second;
      used.erase(used.begin());

      if (sel_e[v] != -1)
        std::cout << v << " " << sel_e[v] << std::endl;

      std::vector<std::pair<Vertex, Vertex>> neigh = test.GetNeighbours(v);
      for (size_t j = 0; j < neigh.size(); ++j) {
        int to = neigh[j].first,
            cost = neigh[j].second;
        if (cost < minostov[to]) {
          used.erase(std::make_pair(minostov[to], to));
          minostov[to] = cost;
          sel_e[to] = v;
          used.insert(std::make_pair(minostov[to], to));
        }
      }
    }*/
  }
}

template <typename Vertex = int64_t, typename Edge = DefaultEdge<Vertex>>
TreeGraph<Vertex, Edge> Kruskala(AdjacencyListGraph<Vertex, Edge> test) {
  int64_t cost = 0;
  DSU<Vertex> ostov;
  vector<pair<int64_t, pair<Vertex, Vertex>>> minost;

  sort(test.SetEdges().begin(), test.SetEdges().end());
  for (int j = 0; j < test.GetVerticesNumber(); ++j) {
    ostov.MakeSet(j);
  }

  for (auto i = 0; i < test.SetEdges().size(); ++i) {
    int64_t begin = test.SetEdges()[i].second.first;
    int64_t end = test.SetEdges()[i].second.second;
    int64_t l = test.SetEdges()[i].first;
    if (ostov.FindSet(begin) != ostov.FindSet(end)) {
      cost += l;
      minost.push_back({l, test.SetEdges()[i].second});
      ostov.UnionSets(begin, end, l);
    }
  }
  std::cout << cost;
   TreeGraph<Vertex, Edge> result_tree(test.GetVerticesNumber(), minost);
   return result_tree;
}

}  // namespace graph


int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  size_t vertex_num = 0;
  size_t edges_num = 0;
  std::cin >> vertex_num >> edges_num;

  vector<graph::DefaultEdge<int64_t>> input_edges;
  for (size_t i = 0; i < edges_num; ++i) {
    int64_t start = 0;
    int64_t finish = 0;
    int64_t weight = 0;
    std::cin >> start >> finish >> weight;
    graph::DefaultEdge<int64_t> input(start, finish, weight);
    input_edges.push_back(input);
  }

  graph::AdjacencyListGraph<int64_t, graph::DefaultEdge<int64_t>> graph(vertex_num,
                                                                input_edges);

  // graph::Kruskala(graph);

  graph::Prima(graph);
  return 0;
}