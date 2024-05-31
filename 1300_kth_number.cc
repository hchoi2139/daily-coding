#include <algorithm>
#include <iostream>

int n, k;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> k;

  int lo = 1;
  int hi = k;

  int ans = -1;

  while (lo <= hi) {
    int mid = (lo + hi) >> 1;
    int cnt = 0;

    for (int i = 1; i <= n; ++i) {
      cnt += std::min(n, mid / i);
    }

    if (cnt >= k) {
      ans = mid;
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }

  std::cout << ans;

  return 0;
}