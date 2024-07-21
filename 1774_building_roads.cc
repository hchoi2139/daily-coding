#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

static constexpr int kMaxN = 1'004;

struct Coord {
  int x, y;
  Coord(int x_coord, int y_coord) : x(x_coord), y(y_coord) {}
};

struct Edge {
  int ia, ib;
  double w;
  Edge(int idx_a, int idx_b, double weight) : ia(idx_a), ib(idx_b), w(weight) {}
  bool operator<(const Edge& e) const { return w < e.w; }
};

[[nodiscard]] inline double l2Dist(const Coord& a, const Coord& b) {
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

vector<Coord> gods;
vector<Edge> edges;
int parent[kMaxN];
int m;
int n;

[[nodiscard]] int findParent(const int x) {
  if (parent[x] != x) {
    parent[x] = findParent(parent[x]);
  }
  return parent[x];
}

void makeUnion(const int x, const int y) {
  const int px = findParent(x);
  const int py = findParent(y);
  parent[max(px, py)] = min(px, py);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cout << fixed;
  cout.precision(2);

  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    parent[i] = i;
  }

  gods.emplace_back(-1, -1);

  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    gods.emplace_back(x, y);
  }

  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    makeUnion(a, b);
  }

  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      edges.emplace_back(i, j, l2Dist(gods[i], gods[j]));
    }
  }

  sort(edges.begin(), edges.end());

  double add_w_sum = 0.0;

  for (const Edge& e : edges) {
    if (findParent(e.ia) != findParent(e.ib)) {
      makeUnion(e.ia, e.ib);
      add_w_sum += e.w;
    }
  }

  cout << add_w_sum;

  return 0;
}
