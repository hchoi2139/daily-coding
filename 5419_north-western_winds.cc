#include <algorithm>
#include <cstring>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

#define MAX_N 75'005

using namespace std;
using pii = pair<int, int>;
using ll = long long;

int tree[4 * MAX_N];
vector<pii> islands;
vector<int> ys;

int range_sum(int node, int l, int r, int s, int e) {
  if (l > e || r < s) {
    return 0;
  }
  if (l <= s && e <= r) {
    return tree[node];
  }
  int m = (s + e) / 2;
  return range_sum(2 * node, l, r, s, m) +
         range_sum(2 * node + 1, l, r, m + 1, e);
}

void update(int node, int idx, int s, int e) {
  if (idx < s || idx > e) {
    return;
  }
  if (s == e) {
    tree[node]++;
    return;
  }
  int m = (s + e) / 2;
  update(2 * node, idx, s, m);
  update(2 * node + 1, idx, m + 1, e);
  tree[node] = tree[2 * node] + tree[2 * node + 1];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;

  while (T--) {
    islands.clear();
    ys.clear();
    memset(tree, 0, sizeof tree);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
      int x, y;
      cin >> x >> y;
      islands.push_back(make_pair(x, y));
      ys.push_back(y);
    }

    sort(islands.begin(), islands.end(), [](pii a, pii b) {
      return a.first < b.first || (a.first == b.first && a.second > b.second);
    });
    sort(ys.begin(), ys.end(), greater<>());

    ll ans = 0;

    for (auto [x, y] : islands) {
      int idx =
          upper_bound(ys.begin(), ys.end(), y, greater<>()) - ys.begin() - 1;
      ans += range_sum(1, 0, idx, 0, n - 1);
      update(1, idx, 0, n - 1);
    }

    cout << ans << '\n';
  }

  return 0;
}
