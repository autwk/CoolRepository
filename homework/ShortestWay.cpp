#include <vector>
#include <iostream>
#include <unordered_set>
#include <limits>
#include <queue>
#include <algorithm>

class Graph {
 private:
  std::vector<std::unordered_set<int>> vertices_;
  std::vector<int> dist_;
  std::vector<int> parents_;

 public:
  explicit Graph(int n) {
    vertices_ = std::vector<std::unordered_set<int>>(n);
    dist_ = std::vector<int>(n, std::numeric_limits<int>::max());
    parents_ = std::vector<int>(n, -1);
  }

  void AddEdge(int v, int u) {
    vertices_[v].insert(u);
    vertices_[u].insert(v);
  }

  void BFS(int start) {
    std::queue<int> q;
    q.push(start);
    dist_[start] = 0;

    while (!q.empty()) {
      int v = q.front();
      q.pop();

      for (auto u : vertices_[v]) {
        if (dist_[u] == std::numeric_limits<int>::max()) {
          dist_[u] = dist_[v] + 1;
          parents_[u] = v;
          q.push(u);
        }
      }
    }
  }

  void ShortestWay(int start, int end) {
    BFS(start);

    if (dist_[end] == std::numeric_limits<int>::max()) {
      std::cout << -1;
      return;
    }

    std::cout << dist_[end] << '\n';
    int x = end;
    std::vector<int> way;

    while (parents_[x] != -1) {
      way.push_back(x);
      x = parents_[x];
    }
    way.push_back(x);

    std::reverse(way.begin(), way.end());
    for (auto v : way) {
      std::cout << v + 1 << " ";
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
  Graph g(n);

  int start, end;
  std::cin >> start >> end;

  for (int i = 0; i < m; ++i) {
    std::cin >> g;
  }

  g.ShortestWay(start - 1, end - 1);
}
