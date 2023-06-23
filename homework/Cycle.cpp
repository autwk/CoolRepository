#include <vector>
#include <iostream>
#include <unordered_set>

enum Colour { WHITE, GREY, BLACK };

class Graph {
 private:
  int n_, m_;
  bool is_cycle_ = false;

  std::vector<std::unordered_set<int>> vertices_;
  std::vector<Colour> colors_;
  std::vector<int> way_;

 public:
  explicit Graph(int n, int m) : n_(n), m_(m) {
    vertices_ = std::vector<std::unordered_set<int>>(n);
    colors_ = std::vector<Colour>(n, WHITE);
  }

  void AddEdge(int v, int u) {
    vertices_[v].insert(u);
  }

  void Cycle() {
    int curr = way_.size() - 2;
    int u = way_.back();

    while (way_[curr] != u) {
      --curr;
    }

    std::cout << "YES" << '\n';
    int size = way_.size();

    for (; curr < size - 1; ++curr) {
      std::cout << way_[curr] + 1 << " ";
    }
  }

  void DFSVisit(int v) {
    if (is_cycle_) {
      return;
    }

    colors_[v] = GREY;
    way_.push_back(v);

    for (auto u : vertices_[v]) {
      if (colors_[u] == GREY) {
        is_cycle_ = true;
        way_.push_back(u);
        Cycle();
        return;
      }

      if (colors_[u] == WHITE) {
        DFSVisit(u);
      }

      if (is_cycle_) {
        return;
      }
    }

    colors_[v] = BLACK;
    way_.pop_back();
  }

  void DFS() {
    for (int i = 0; i < n_; ++i) {
      if (colors_[i] == WHITE) {
        DFSVisit(i);

        if (is_cycle_) {
          break;
        }
      }
    }

    if (!is_cycle_) {
      std::cout << "NO";
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
}
