#include <vector>
#include <iostream>
#include <unordered_map>
#include <map>
#include <set>
#include <limits>

enum Colour { WHITE, GREY, BLACK };

class Graph {
 private:
  int n_, m_;
  int time_ = -1;

  std::vector<std::unordered_map<int, int>> vertices_;
  std::vector<int> time_in_;
  std::vector<int> time_up_;
  std::vector<Colour> colors_;
  std::set<int> bridges_;

 public:
  explicit Graph(int n, int m) : n_(n), m_(m) {
    vertices_ = std::vector<std::unordered_map<int, int>>(n);
    time_in_ = std::vector<int>(n, std::numeric_limits<int>::max());
    time_up_ = std::vector<int>(n, std::numeric_limits<int>::max());
    colors_ = std::vector<Colour>(n, WHITE);
  }

  void AddEdge(int v, int u, int number) {
    vertices_[v].insert({number, u});
    vertices_[u].insert({number, v});
  }

  bool IsMultiple(int v, int u) {
    int count = 0;

    for (auto x : vertices_[v]) {
      if (x.second == u) {
        ++count;
      }
    }

    return (count > 1);
  }

  void DFSVisit(int v, int parent = -1) {
    colors_[v] = GREY;
    time_in_[v] = time_up_[v] = ++time_;

    for (auto x : vertices_[v]) {
      int u = x.second;

      if (u == parent) {
        continue;
      }

      if (colors_[u] == GREY) {
        time_up_[v] = std::min(time_up_[v], time_in_[u]);
      }

      if (colors_[u] == WHITE) {
        DFSVisit(u, v);
        time_up_[v] = std::min(time_up_[v], time_up_[u]);

        if (time_in_[v] < time_up_[u] && !IsMultiple(v, u)) {
          bridges_.insert(x.first);
        }
      }
    }

    colors_[v] = BLACK;
  }

  void DFS() {
    time_ = -1;

    for (int i = 0; i < n_; ++i) {
      if (colors_[i] == WHITE) {
        DFSVisit(i);
      }
    }
  }

  void Bridges() {
    std::cout << bridges_.size() << '\n';

    for (auto edge : bridges_) {
      std::cout << edge + 1 << ' ';
    }
  }
};

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph g(n, m);

  for (int i = 0; i < m; ++i) {
    int v, u;
    std::cin >> v >> u;
    g.AddEdge(v - 1, u - 1, i);
  }

  g.DFS();
  g.Bridges();
}
