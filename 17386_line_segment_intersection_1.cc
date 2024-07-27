#include <iostream>
#include <utility>

using ll = long long;
using pll = std::pair<ll, ll>;

[[nodiscard]] inline ll ccw(const pll& p, const pll& q, const pll& r) {
  const pll a = { q.first - p.first, q.second - p.second };
  const pll b = { r.first - p.first, r.second - p.second };
  const ll cp = a.first * b.second - a.second * b.first;
  if (cp == 0) {
    return 0;
  }
  return cp < 0 ? -1 : 1;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  ll x1, y1, x2, y2;
  std::cin >> x1 >> y1 >> x2 >> y2;

  const pll a = { x1, y1 };
  const pll b = { x2, y2 };

  std::cin >> x1 >> y1 >> x2 >> y2;

  const pll c = { x1, y1 };
  const pll d = { x2, y2 };

  const ll abc = ccw(a, b, c);
  const ll abd = ccw(a, b, d);
  const ll cda = ccw(c, d, a);
  const ll cdb = ccw(c, d, b);

  if (abc * abd <= 0 && cda * cdb <= 0) {
    std::cout << 1;
  } else {
    std::cout << 0;
  }

  return 0;
}
