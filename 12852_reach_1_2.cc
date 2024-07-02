#include <algorithm>
#include <iostream>

using namespace std;

static constexpr size_t kMaxN = 1'000'004;

int dp[kMaxN];
size_t n;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  dp[0] = -1;
  dp[1] = 0;

  for (size_t i = 2; i <= n; i++) {
    dp[i] = dp[i - 1] + 1;

    if (i % 3 == 0) {
      dp[i] = min(dp[i], dp[i / 3] + 1);
    }

    if (i % 2 == 0) {
      dp[i] = min(dp[i], dp[i / 2] + 1);
    }
  }

  cout << dp[n] << '\n';

  while (n != 0) {
    cout << n << ' ';

    if (dp[n] == dp[n - 1] + 1) {
      n -= 1;
    }
    else if (n % 2 == 0 && dp[n] == dp[n / 2] + 1) {
      n /= 2;
    }
    else if (n % 3 == 0 && dp[n] == dp[n / 3] + 1) {
      n /= 3;
    }
  }

  return 0;
}
