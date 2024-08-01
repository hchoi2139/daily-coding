#include <algorithm>
#include <iostream>

using namespace std;

static constexpr int kInf = 0x3f3f3f3f;

int n;

int cost[1000][3];
int dp[1000][3];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> cost[i][0] >> cost[i][1] >> cost[i][2];
  }

  int ans = kInf;

  for (int col = 0; col < 3; col++) {
    dp[0][col] = cost[0][col];
    dp[0][(col + 1) % 3] = kInf;
    dp[0][(col + 2) % 3] = kInf;

    for (int i = 1; i < n; i++) {
      dp[i][0] = cost[i][0] + min(dp[i - 1][1], dp[i - 1][2]);
      dp[i][1] = cost[i][1] + min(dp[i - 1][0], dp[i - 1][2]);
      dp[i][2] = cost[i][2] + min(dp[i - 1][0], dp[i - 1][1]);
    }

    ans = min({ ans, dp[n - 1][(col + 1) % 3], dp[n - 1][(col + 2) % 3] });
  }

  cout << ans;

  return 0;
}
