#include <algorithm>
#include <cstring>
#include <iostream>

static constexpr int kMaxN = 20;
static constexpr int kInf = 0x3f3f3f3f;
static constexpr int kUnvisited = -1;

inline int on(int val, int i) {
  return val | (1 << i);
}

inline int off(int val, int i) {
  return val & ~(1 << i);
}

inline int is_on(int val, int i) {
  return val & (1 << i);
}

int cost[kMaxN][kMaxN];
int dp[kMaxN][1 << (kMaxN + 1)];
int n;

void Input() {
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> cost[i][j];
    }
  }
}

int DFS(const int p, const int vis) {
  // Job has been assigned to every person.
  if (vis == (1 << n) - 1) {
    return 0;
  }
  // Cached info.
  if (dp[p][vis] != kUnvisited) {
    return dp[p][vis];
  }

  dp[p][vis] = kInf;

  for (int i = 0; i < n; i++) {
    // Job i has already been assigned to someone.
    if (is_on(vis, i)) {
      continue;
    }
    dp[p][vis] = std::min(dp[p][vis], DFS(p + 1, on(vis, i)) + cost[p][i]);
  }

  return dp[p][vis];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Input();

  std::memset(dp, kUnvisited, sizeof(dp));

  std::cout << DFS(0, 0);

  return 0;
}
