#include <iostream>

#define MAX_N 1'005
#define MAX_K 1'005
#define MOD 1'000'000'003

using namespace std;

int dp[MAX_N][MAX_K];
int n, k;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k;

  for (int i = 1; i <= n; i++) {
    dp[i][0] = 1;
    dp[i][1] = i;
  }

  for (int i = 2; i < n; i++) {
    for (int j = 2; j <= k; j++) {
      dp[i][j] = (dp[i - 1][j] + dp[i - 2][j - 1]) % MOD;
    }
  }

  cout << (dp[n - 1][k] + dp[n - 3][k - 1]) % MOD;

  return 0;
}
