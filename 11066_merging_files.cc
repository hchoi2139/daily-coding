#include <algorithm>
#include <iostream>
#include <limits>

static constexpr int kInf = std::numeric_limits<int>::max();
static constexpr int kMaxK = 505;

int dp[kMaxK][kMaxK];
int file_sum[kMaxK];
int t, k;

[[nodiscard]] inline int psum(int start, int end) {
  return file_sum[end] - file_sum[start - 1];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> t;

  while (t--) {
    std::cin >> k;

    for (int i = 1; i <= k; i++) {
      std::cin >> file_sum[i];
      file_sum[i] += file_sum[i - 1];
    }
    
    for (int j = 2; j <= k; j++) {
      for (int i = j - 1; i >= 1; i--) {
        dp[i][j] = kInf;
        for (int k = i; k < j; k++) {
          dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k + 1][j] + psum(i, j));
        }
      }
    }

    std::cout << dp[1][k] << '\n';
  }

  return 0;
}