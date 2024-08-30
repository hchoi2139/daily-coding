#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, M;
  cin >> N >> M;

  vector<pll> revs;

  for (int i = 0; i < N; i++) {
    ll x, y;
    cin >> x >> y;
    if (x > y) {
      revs.push_back(make_pair(x, y));
    }
  }

  sort(revs.begin(), revs.end(), greater<>());

  ll r = (ll)numeric_limits<int>::max();
  ll l = (ll)numeric_limits<int>::max();
  ll rev_tot_len = 0;

  for (auto [x, y] : revs) {
    if (x < l) {
      rev_tot_len += r - l;
      r = x;
      l = y;
    } else {
      l = min(l, y);
    }
  }
  rev_tot_len += r - l;

  cout << M + 2 * rev_tot_len;

  return 0;
}
