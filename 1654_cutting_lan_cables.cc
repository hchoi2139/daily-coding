#include <algorithm>
#include <iostream>

using ll = long long;

static constexpr ll kMaxK = 10005;

ll lens[kMaxK];
ll k, n, max_len;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> k >> n;

  for (int i = 0; i < k; ++i) {
    std::cin >> lens[i];
    max_len = std::max(max_len, lens[i]);
  }

  ll ans = 0;
  ll lo = 1;
  ll hi = max_len;

  while (lo <= hi) {
    ll mid = ((lo ^ hi) >> 1) + (lo & hi);

    ll cnt = 0;
    for (int i = 0; i < k; ++i) {
      cnt += lens[i] / mid;
    }

    if (cnt < n) {
      hi = mid - 1;
    } else {
      ans = std::max(ans, mid);
      lo = mid + 1;
    }
  }

  std::cout << ans;

  return 0;
}