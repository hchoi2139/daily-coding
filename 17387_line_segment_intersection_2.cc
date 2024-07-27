#include <iostream>
#include <utility>

using ll = long long;
using pll = std::pair<ll, ll>;

ll ccw(const pll& p, const pll& q, const pll& r) {
  const pll a = { q.first - p.first, q.second - p.second };
  const pll b = { r.first - p.first, r.second - p.second };
  const ll cp = a.first * b.second - a.second * b.first;
  if (cp == 0) {
    return 0;
  }
  return cp < 0 ? -1 : 1;
}

bool DoIntersect(const pll& p, const pll& q, const pll& r, const pll& s) {
  const ll pq = ccw(p, q, r) * ccw(p, q, s);
  const ll rs = ccw(r, s, p) * ccw(r, s, q);

  if (pq == 0 && rs == 0) {
    return p <= s && r <= q;
  }

  return pq <= 0 && rs <= 0;
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

  std::cout << (DoIntersect(std::min(a, b), std::max(a, b), std::min(c, d),
                            std::max(c, d))
                    ? 1
                    : 0);

  return 0;
}
