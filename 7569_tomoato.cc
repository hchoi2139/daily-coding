#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>

static constexpr int kMaxM = 105;
static constexpr int kMaxN = 105;
static constexpr int kMaxH = 105;

static constexpr int kNumDirs = 6;
static constexpr int kDi[] = { 0, 0, -1, 1, 0, 0 };
static constexpr int kDj[] = { 1, -1, 0, 0, 0, 0 };
static constexpr int kDk[] = { 0, 0, 0, 0, 1, -1 };

using namespace std;

queue<tuple<int, int, int>> q;

int graph[kMaxN][kMaxM][kMaxH];
int m, n, h;

[[nodiscard]] inline bool is_inside_the_graph(int i, int j, int k) {
  return 0 <= i && i < n && 0 <= j && j < m && 0 <= k && k < h;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> m >> n >> h;

  for (int k = 0; k < h; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> graph[i][j][k];
        if (graph[i][j][k] == 1) {
          q.emplace(i, j, k);
        }
      }
    }
  }

  while (!q.empty()) {
    const auto [i, j, k] = q.front();
    q.pop();

    for (int d = 0; d < kNumDirs; d++) {
      int ni = i + kDi[d];
      int nj = j + kDj[d];
      int nk = k + kDk[d];
      if (is_inside_the_graph(ni, nj, nk) && graph[ni][nj][nk] == 0) {
        graph[ni][nj][nk] = graph[i][j][k] + 1;
        q.emplace(ni, nj, nk);
      }
    }
  }

  int res = -1;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < h; k++) {
        if (graph[i][j][k] == 0) {
          cout << "-1";
          return 0;
        }
        res = max(res, graph[i][j][k]);
      }
    }
  }

  cout << res - 1;

  return 0;
}