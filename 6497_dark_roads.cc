#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

static constexpr int kMaxM = 200'000;

struct Edge {
  int a, b, w;
  Edge(int node1, int node2, int weight) : a(node1), b(node2), w(weight) {}
  bool operator<(const Edge& e) const { return w < e.w; }
};

vector<Edge> edges;
int parent[kMaxM];
int m, n;

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

  while (true) {
    cin >> m >> n;

    if (m == 0 && n == 0) {
      break;
    }

    int tot_w_sum = 0;
    int mst_w_sum = 0;

    for (int i = 0; i < m; i++) {
      parent[i] = i;
    }

    edges.clear();

    for (int i = 0; i < n; i++) {
      int x, y, z;
      cin >> x >> y >> z;
      edges.emplace_back(x, y, z);
      tot_w_sum += z;
    }

    sort(edges.begin(), edges.end());

    for (const Edge& e : edges) {
      if (findParent(e.a) != findParent(e.b)) {
        makeUnion(e.a, e.b);
        mst_w_sum += e.w;
      }
    }

    cout << tot_w_sum - mst_w_sum << '\n';
  }

  return 0;
}
