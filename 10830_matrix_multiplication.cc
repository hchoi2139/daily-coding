#include <iostream>

using ll = long long;

static constexpr int kDiv = 1000;
static constexpr int kMaxN = 5;

int a[kMaxN][kMaxN], ans[kMaxN][kMaxN], tmp[kMaxN][kMaxN];
int n;
ll power;

void mat_mul(int (&x)[kMaxN][kMaxN], const int (&y)[kMaxN][kMaxN]) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      tmp[i][j] = 0;
      for (int k = 0; k < n; ++k) {
        tmp[i][j] += (x[i][k] * y[k][j]);
      }
      tmp[i][j] %= kDiv;
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      x[i][j] = tmp[i][j];
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> power;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> a[i][j];
    }
    ans[i][i] = 1;
  }

  while (power > 0) {
    if (power % 2 == 1) {
      mat_mul(ans, a);
    }
    mat_mul(a, a);
    power /= 2;
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << ans[i][j] << ' ';
    }
    std::cout << '\n';
  }

  return 0;
}