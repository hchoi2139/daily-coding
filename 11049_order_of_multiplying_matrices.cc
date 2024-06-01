#include <algorithm>
#include <iostream>
#include <limits>

static constexpr int kInf = std::numeric_limits<int>::max();
static constexpr int kMaxN = 505;

int dp[kMaxN][kMaxN];
int rows[kMaxN], cols[kMaxN];
int n;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;

  for (int i = 1; i <= n; i++) {
    std::cin >> rows[i] >> cols[i];
  }

  for (int j = 2; j <= n; j++) {
    for (int i = j - 1; i >= 1; i--) {
      dp[i][j] = kInf;
      for (int k = i; k < j; k++) {
        dp[i][j] = std::min(
            dp[i][j], dp[i][k] + dp[k + 1][j] + rows[i] * cols[k] * cols[j]);
      }
    }
  }

  std::cout << dp[1][n];

  return 0;
}