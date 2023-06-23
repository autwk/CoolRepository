#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

class Graph {
 private:
  int n_;
  std::vector<std::vector<int>> vertices_;

 public:
  explicit Graph(int n) : n_(n) {
    vertices_.resize(n, std::vector<int>(n));
  }

  void In() {
    for (int i = 0; i < n_; ++i) {
      for (int j = 0; j < n_; ++j) {
        std::cin >> vertices_[i][j];
      }
    }
  }

  void Floyd() {
    for (int k = 0; k < n_; ++k) {
      for (int x = 0; x < n_; ++x) {
        for (int y = 0; y < n_; ++y) {
          vertices_[x][y] = std::min(vertices_[x][y], vertices_[x][k] + vertices_[k][y]);
        }
      }
    }
  }

  void Out() {
    for (int i = 0; i < n_; ++i) {
      for (int j = 0; j < n_; ++j) {
        std::cout << vertices_[i][j] << " ";
      }

      std::cout << '\n';
    }
  }
};

int main() {
  int n;
  std::cin >> n;

  Graph g(n);
  g.In();
  g.Floyd();
  g.Out();
}
