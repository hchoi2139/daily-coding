#include <algorithm>
#include <cstring>
#include <iostream>

static constexpr int kMaxN = 16;
static constexpr int kInf = 0x3f3f3f3f;
static constexpr int kUnVis = -1;
static constexpr int kStart = 0;

inline int on(const int val, const int i) {
  return val | (1 << i);
}

inline int off(const int val, const int i) {
  return val & ~(1 << i);
}

inline int is_on(const int val, const int i) {
  return val & (1 << i);
}

int cost[kMaxN][kMaxN];
int dp[kMaxN][1 << kMaxN];
int n;

void Input() {
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> cost[i][j];
    }
  }
}

int DFS(const int cur, const int vis) {
  // Visited all cities.
  if (vis == (1 << n) - 1) {
    return cost[cur][kStart] != 0 ? cost[cur][kStart] : kInf;
  }
  // Cached info.
  if (dp[cur][vis] != kUnVis) {
    return dp[cur][vis];
  }

  dp[cur][vis] = kInf;

  for (int nxt = 0; nxt < n; nxt++) {
    // If nxt is unreachable from cur, omit.
    if (cost[cur][nxt] == 0) {
      continue;
    }
    // If nxt was visited, omit.
    if (is_on(vis, nxt)) {
      continue;
    }

    dp[cur][vis] =
        std::min(dp[cur][vis], DFS(nxt, on(vis, nxt)) + cost[cur][nxt]);
  }

  return dp[cur][vis];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Input();

  std::memset(dp, kUnVis, sizeof(dp));

  std::cout << DFS(kStart, 1);

  return 0;
}
