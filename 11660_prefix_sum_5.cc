#include <iostream>

static constexpr int kMaxN = 1025;

int table[kMaxN][kMaxN], p_sum[kMaxN][kMaxN];
int n, m;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      std::cin >> table[i][j];
      p_sum[i][j] =
          table[i][j] + p_sum[i - 1][j] + p_sum[i][j - 1] - p_sum[i - 1][j - 1];
    }
  }

  int x1, y1, x2, y2;
  for (int t = 0; t < m; ++t) {
    std::cin >> x1 >> y1 >> x2 >> y2;
    std::cout << p_sum[x2][y2] - p_sum[x1 - 1][y2] - p_sum[x2][y1 - 1] +
                     p_sum[x1 - 1][y1 - 1]
              << '\n';
  }

  return 0;
}
