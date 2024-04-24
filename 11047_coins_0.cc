#include <iostream>

static constexpr int kMaxN = 15;

int n, k, coins[kMaxN];

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> k;

  for (int i = 0; i < n; ++i) {
    std::cin >> coins[i];
  }

  int num_coins = 0;

  for (int i = n - 1; i >= 0; --i) {
    num_coins += k / coins[i];
    k %= coins[i];
  }

  std::cout << num_coins;

  return 0;
}
