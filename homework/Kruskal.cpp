#include <vector>
#include <iostream>

class DSU {
 private:
  std::vector<int> parent_;
  std::vector<int> rank_;

 public:
  explicit DSU(int n) {
    rank_ = std::vector<int>(n, 0);
    parent_ = std::vector<int>(n, -1);
  }

  int FindSet(int x) {
    if (parent_[x] == -1) {
      return x;
    }

    return parent_[x] = FindSet(parent_[x]);
  }

  void Union(int x, int y) {
    x = FindSet(x);
    y = FindSet(y);

    if (rank_[x] < rank_[y]) {
      parent_[x] = y;
    } else if (rank_[y] < rank_[x]) {
      parent_[y] = x;
    } else {
      parent_[x] = y;
      rank_[y] += 1;
    }
  }
};

struct Edge {
  int first;
  int second;
  int cost;
};

class Graph {
 private:
  int n_;
  int m_;
  std::vector<Edge> sorted_edges_;

 public:
  std::vector<Edge> mst;

  Graph(int n, int m) : n_(n), m_(m) {
  }

  void AddEdge(int v, int u, int cost) {
    sorted_edges_.push_back({v, u, cost});
  }

  void Kruskal() {
    DSU dsu(n_);

    for (auto edge : sorted_edges_) {
      if (dsu.FindSet(edge.first) != dsu.FindSet(edge.second)) {
        dsu.Union(edge.first, edge.second);
        mst.push_back(edge);
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
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  Graph g(n, m);

  for (int i = 0; i < m; ++i) {
    std::cin >> g;
  }

  g.Kruskal();
  int sum = 0;

  for (auto edge : g.mst) {
    sum += edge.cost;
  }

  std::cout << sum;
}
