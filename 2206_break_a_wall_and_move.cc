#include <cstdio>
#include <queue>
#include <utility>

using namespace std;

static constexpr int kMaxN = 1005;
static constexpr int kMaxM = 1005;

static constexpr int kInitRow = 1;
static constexpr int kInitCol = 1;

static constexpr int kIsNotWall = 0;
static constexpr int kIsWall = 1;
static constexpr int kIsNotBroken = 0;
static constexpr int kIsBroken = 1;

static constexpr pair<int, int> kDir[] = {
  { 0, 1 },
  { 0, -1 },
  { -1, 0 },
  { 1, 0 },
};

struct Pos {
  int i;
  int j;
  int is_broken;
};

queue<Pos> q;
int map[kMaxN][kMaxM];
int vis[kMaxN][kMaxM][2];
int n, m;

int main() {
  scanf("%d %d", &n, &m);

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf("%1d", &map[i][j]);
    }
  }

  vis[kInitRow][kInitCol][kIsNotBroken] = 1;
  q.push({ kInitRow, kInitCol, kIsNotBroken });

  while (!q.empty()) {
    Pos cur = q.front();
    q.pop();

    if (cur.i == n && cur.j == m) {
      printf("%d", vis[n][m][cur.is_broken]);
      return 0;
    }

    for (const auto& [di, dj] : kDir) {
      int nxt_i = cur.i + di;
      int nxt_j = cur.j + dj;

      if (nxt_i < kInitRow || n < nxt_i || nxt_j < kInitCol || m < nxt_j) {
        continue;
      }

      if (vis[nxt_i][nxt_j][cur.is_broken] != 0) {
        continue;
      }

      if (map[nxt_i][nxt_j] == kIsNotWall) {
        vis[nxt_i][nxt_j][cur.is_broken] = vis[cur.i][cur.j][cur.is_broken] + 1;
        q.push({ nxt_i, nxt_j, cur.is_broken });
      }
      else if (map[nxt_i][nxt_j] == kIsWall && cur.is_broken == kIsNotBroken) {
        vis[nxt_i][nxt_j][kIsBroken] = vis[cur.i][cur.j][kIsNotBroken] + 1;
        q.push({ nxt_i, nxt_j, kIsBroken });
      }
    }
  }

  printf("-1");

  return 0;
}