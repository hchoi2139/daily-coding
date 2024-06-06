#include <iostream>

static constexpr int kMaxNumCoins = 105;
static constexpr int kMaxPrice = 10005;

int coins[kMaxNumCoins];
int dp[kMaxPrice];

int num_coins, tar_price;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> num_coins >> tar_price;

  for (int i = 1; i <= num_coins; i++) {
    std::cin >> coins[i];
  }

  dp[0] = 1;

  for (int c = 1; c <= num_coins; c++) {
    for (int p = coins[c]; p <= tar_price; p++) {
      dp[p] += dp[p - coins[c]];
    }
  }

  std::cout << dp[tar_price];

  return 0;
}