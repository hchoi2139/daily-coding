#include <algorithm>
#include <iostream>

static constexpr int kMaxM = 505;
static constexpr int kMaxN = 505;

int map[kMaxM][kMaxN], dp[kMaxM][kMaxN];
int m, n;

int dr[] = { 0, 0, -1, 1 };
int dc[] = { 1, -1, 0, 0 };

int dfs(int r, int c) {
  if (r == m && c == n)
    return 1;

  if (dp[r][c] != -1)
    return dp[r][c];

  dp[r][c] = 0;

  for (int i = 0; i < 4; i++) {
    int nr = r + dr[i];
    int nc = c + dc[i];
    
    if (1 <= nr && nr <= m && 1 <= nc && nc <= n) {
      if (map[nr][nc] < map[r][c]) {
        dp[r][c] += dfs(nr, nc);
      }
    }
  }

  return dp[r][c];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> m >> n;

  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      std::cin >> map[i][j];
      dp[i][j] = -1;
    }
  }

  std::cout << dfs(1, 1);

  return 0;
}