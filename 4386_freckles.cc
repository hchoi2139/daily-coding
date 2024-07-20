#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

static constexpr int kMaxNumStars = 104;

struct Coord {
  double x, y;
  Coord(int x, int y) : x(x), y(y) {}
};

struct Edge {
  int ia, ib;
  double w;
  Edge(int idx_a, int idx_b, double weight) : ia(idx_a), ib(idx_b), w(weight) {}
  bool operator<(const Edge& e) const { return w < e.w; }
};

[[nodiscard]] inline double l2_dist(const Coord& a, const Coord& b) {
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

vector<Coord> stars;
vector<Edge> edges;
int parent[kMaxNumStars];
int num_stars;

[[nodiscard]] int find_parent(const int x) {
  if (parent[x] != x) {
    parent[x] = find_parent(parent[x]);
  }
  return parent[x];
}

void make_union(const int x, const int y) {
  const int px = find_parent(x);
  const int py = find_parent(y);
  parent[max(px, py)] = min(px, py);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> num_stars;

  double x;
  double y;

  for (int i = 0; i < num_stars; i++) {
    cin >> x >> y;
    stars.emplace_back(x, y);
  }

  for (size_t i = 0; i < stars.size(); i++) {
    const Coord star_i = stars[i];

    for (size_t j = i + 1; j < stars.size(); j++) {
      const Coord star_j = stars[j];

      edges.emplace_back(i, j, l2_dist(star_i, star_j));
    }
  }

  sort(edges.begin(), edges.end());

  for (int i = 1; i <= num_stars; i++) {
    parent[i] = i;
  }

  double w_sum = 0.0;

  for (const Edge& e : edges) {
    if (find_parent(e.ia) != find_parent(e.ib)) {
      make_union(e.ia, e.ib);
      w_sum += e.w;
    }
  }

  cout << w_sum;

  return 0;
}
