#include <vector>
#include <iostream>
#include <unordered_set>
#include <set>
#include <limits>

enum Colour { WHITE, GREY, BLACK };

class Graph {
 private:
  int n_, m_;
  int time_ = -1;

  std::vector<std::unordered_set<int>> vertices_;
  std::vector<int> time_in_;
  std::vector<int> time_up_;
  std::vector<Colour> colors_;
  std::set<int> articulation_points_;

 public:
  explicit Graph(int n, int m) : n_(n), m_(m) {
    vertices_ = std::vector<std::unordered_set<int>>(n);
    time_in_ = std::vector<int>(n, std::numeric_limits<int>::max());
    time_up_ = std::vector<int>(n, std::numeric_limits<int>::max());
    colors_ = std::vector<Colour>(n, WHITE);
  }

  void AddEdge(int v, int u) {
    vertices_[v].insert(u);
    vertices_[u].insert(v);
  }

  void DFSVisit(int v, bool is_root = true) {
    colors_[v] = GREY;
    time_in_[v] = time_up_[v] = ++time_;
    int n_child = 0;

    for (auto u : vertices_[v]) {
      if (colors_[u] == GREY) {
        time_up_[v] = std::min(time_up_[v], time_in_[u]);
      }

      if (colors_[u] == WHITE) {
        ++n_child;
        DFSVisit(u, false);
        time_up_[v] = std::min(time_up_[v], time_up_[u]);

        if (!is_root && time_in_[v] <= time_up_[u]) {
          articulation_points_.insert(v);
        }
      }
    }

    if (is_root && n_child >= 2) {
      articulation_points_.insert(v);
    }

    colors_[v] = BLACK;
  }

  void DFS() {
    for (int i = 0; i < n_; ++i) {
      if (colors_[i] == WHITE) {
        DFSVisit(i);
      }
    }
  }

  void ArticulationPoints() {
    std::cout << articulation_points_.size() << '\n';

    for (int x : articulation_points_) {
      std::cout << x + 1 << ' ';
    }
  }
};

std::istream& operator>>(std::istream& in, Graph& g) {
  int v, u;
  in >> v >> u;
  g.AddEdge(v - 1, u - 1);
  return in;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph g(n, m);

  for (int i = 0; i < m; ++i) {
    std::cin >> g;
  }

  g.DFS();
  g.ArticulationPoints();
}
