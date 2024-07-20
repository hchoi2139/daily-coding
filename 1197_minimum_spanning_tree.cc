#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

static constexpr int kMaxV = 10'004;

struct Edge {
  int u, v, w;
  Edge(int a, int b, int weight) : u(a), v(b), w(weight) {}
  bool operator<(const Edge& y) const { return w < y.w; }
};

vector<Edge> graph;
int parent[kMaxV];
int v, e;

[[nodiscard]] int find_parent(const int x) {
  if (parent[x] != x) {
    parent[x] = find_parent(parent[x]);
  }
  return parent[x];
}

void union_parent(const int x, const int y) {
  const int px = find_parent(x);
  const int py = find_parent(y);
  parent[max(px, py)] = min(px, py);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> v >> e;

  for (int i = 1; i <= v; i++) {
    parent[i] = i;
  }

  int a, b, c;

  for (int i = 0; i < e; i++) {
    cin >> a >> b >> c;
    graph.emplace_back(a, b, c);
  }

  sort(graph.begin(), graph.end());

  int weight_sum = 0;

  for (const auto& e : graph) {
    if (find_parent(e.u) != find_parent(e.v)) {
      union_parent(e.u, e.v);
      weight_sum += e.w;
    }
  }

  cout << weight_sum;

  return 0;
}
