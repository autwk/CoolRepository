#include <vector>
#include <iostream>
#include <limits>
#include <set>
#include <algorithm>

struct Edge {
  int second;
  int cost;
};

bool operator<(Edge& first, Edge& second) {
  return first.cost > second.cost;
}

bool operator==(const Edge& first, const Edge& second) {
  return first.cost == second.cost && first.second == second.second;
}

class Graph {
 private:
  int n_;
  int m_;

  std::vector<std::vector<Edge>> vertices_;
  std::vector<int> dist_;
  std::vector<Edge> prev_;

 public:
  int mst = 0;

  Graph(int n, int m) : n_(n), m_(m) {
    vertices_ = std::vector<std::vector<Edge>>(n);
    dist_ = std::vector<int>(n, std::numeric_limits<int>::max());
    dist_[0] = 0;
    prev_ = std::vector<Edge>(n, {-1, -1});
  }

  void AddEdge(int v, int u, int cost) {
    vertices_[v].push_back(Edge{u, cost});
    vertices_[u].push_back(Edge{v, cost});
  }

  void Prim() {
    std::vector<Edge> heap;
    heap.emplace_back(Edge{0, 0});

    while (!heap.empty()) {
      std::pop_heap(heap.begin(), heap.end());
      Edge v = heap.back();
      heap.pop_back();

      if (prev_[v.second] == Edge{-1, -1}) {
        mst += v.cost;
        prev_[v.second] = v;
      }

      for (auto neighbor : vertices_[v.second]) {
        if (prev_[neighbor.second] == Edge{-1, -1} && neighbor.cost < dist_[neighbor.second]) {
          dist_[neighbor.second] = neighbor.cost;
          heap.emplace_back(neighbor);
          std::push_heap(heap.begin(), heap.end());
        }
      }
    }
  }
};

std::istream& operator>>(std::istream& in, Graph& g) {
  int v, u, cost;
  in >> v >> u >> cost;
  g.AddEdge(v - 1, u - 1, cost);
  return in;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph g(n, m);

  for (int i = 0; i < m; ++i) {
    std::cin >> g;
  }

  g.Prim();
  std::cout << g.mst;
}
