#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using ii = std::pair<int, int>;

static constexpr ii kDir[4] = { { 0, 1 }, { 0, -1 }, { -1, 0 }, { 1, 0 } };

static constexpr int kMinLabel = 2;

static constexpr int kMaxN = 12;
static constexpr int kMaxM = 12;
static constexpr int kMaxNumIslands = 10;

static constexpr int kLand = 1;
static constexpr int kSea = 0;

struct Edge {
  int a, b, w;
  Edge(int node1, int node2, int weight) : a(node1), b(node2), w(weight) {}
  bool operator<(const Edge& e) const { return this->w < e.w; }
};

std::vector<Edge> edges;
int parent[kMaxNumIslands];
int map[kMaxN][kMaxM];
int n, m;
int max_label;

[[nodiscard]] int findParent(const int x) {
  if (parent[x] != x) {
    parent[x] = findParent(parent[x]);
  }
  return parent[x];
}

void makeUnion(const int x, const int y) {
  const int px = findParent(x);
  const int py = findParent(y);
  parent[std::max(px, py)] = std::min(px, py);
}

void Input() {
  std::cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      std::cin >> map[i][j];
    }
  }
}

void LabelAnIslandAt(const int r, const int c, const int label) {
  std::queue<ii> q;
  map[r][c] = label;
  q.emplace(r, c);

  while (!q.empty()) {
    const auto [r, c] = q.front();
    q.pop();

    for (const auto& [dr, dc] : kDir) {
      const int nr = r + dr;
      const int nc = c + dc;

      if (1 <= nr && nr <= n && 1 <= nc && nc <= m) {
        if (map[nr][nc] == kLand) {
          map[nr][nc] = label;
          q.emplace(nr, nc);
        }
      }
    }
  }
}

void LabelIslands() {
  int island_no = kMinLabel;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (map[i][j] == kLand) {
        LabelAnIslandAt(i, j, island_no);
        island_no++;
      }
    }
  }
  max_label = island_no - 1;
}

void ConnectABridgeAt(const int r, const int c, const int dr, const int dc) {
  const int label = map[r][c];
  int bridge_len = 0;
  int nr = r;
  int nc = c;

  while (true) {
    nr += dr;
    nc += dc;

    if (nr < 1 || nr > n || nc < 1 || nc > m || map[nr][nc] == label) { return; }

    if (map[nr][nc] == kSea) {
      bridge_len++;
    } else {
      if (bridge_len >= 2) {
        edges.emplace_back(label, map[nr][nc], bridge_len);
      }
      return;
    }
  }
}

void FindAllBridges() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (map[i][j] != kSea) {
        for (const auto& [di, dj] : kDir) {
          ConnectABridgeAt(i, j, di, dj);
        }
      }
    }
  }
}

int FindMST() {
  std::sort(edges.begin(), edges.end());

  for (int i = kMinLabel; i <= max_label ; i++) {
    parent[i] = i;
  }

  int mst_w_sum = 0;

  for (const Edge& e : edges) {
    if (findParent(e.a) != findParent(e.b)) {
      makeUnion(e.a, e.b);
      mst_w_sum += e.w;
    }
  }

  const int root = findParent(kMinLabel);

  for (int i = kMinLabel + 1; i <= max_label; i++) {
    if (findParent(i) != root) {
      return -1;
    }
  }

  return mst_w_sum;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Input();
  LabelIslands();
  FindAllBridges();
  const int min_bridge_len_sum = FindMST();

  std::cout << min_bridge_len_sum;

  return 0;
}
