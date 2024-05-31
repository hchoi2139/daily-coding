#include <algorithm>
#include <iostream>
#include <limits>

static constexpr int kMaxN = 200005;

int xs[kMaxN];
int n, c;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> c;

  for (int i = 0; i < n; ++i) {
    std::cin >> xs[i];
  }

  std::sort(xs, xs + n);

  int lo = 1;
  int hi = xs[n - 1] - xs[0];

  int ans = -1;

  while (lo <= hi) {
    int mid = (lo + hi) / 2;

    int prev_x = xs[0];
    int cnt = 1;

    for (int i = 1; i < n; ++i) {
      if (xs[i] - prev_x >= mid) {
        prev_x = xs[i];
        cnt += 1;
      }
    }

    if (cnt >= c) {
      ans = std::max(ans, mid);
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }

  std::cout << ans;

  return 0;
}