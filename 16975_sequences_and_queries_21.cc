#include <iostream>

#define MAX_N 100'005

using namespace std;
using ll = long long;

ll tree[4 * MAX_N];
ll arr[MAX_N];

void build(int node, int s, int e) {
  if (s == e) {
    tree[node] = arr[s];
    return;
  }
  tree[node] = 0;
  int m = (s + e) / 2;
  build(2 * node, s, m);
  build(2 * node + 1, m + 1, e);
}

void range_sum(int node, int l, int r, int s, int e, ll amt) {
  if (l > e || r < s) {
    return;
  }
  if (l <= s && e <= r) {
    tree[node] += amt;
    return;
  }
  int m = (s + e) / 2;
  range_sum(2 * node, l, r, s, m, amt);
  range_sum(2 * node + 1, l, r, m + 1, e, amt);
}

ll kth(int node, int idx, int s, int e, ll ans) {
  if (idx < s || idx > e) {
    return 0;
  }
  ans += tree[node];
  if (s == e) {
    return ans;
  }
  int m = (s + e) / 2;
  return kth(2 * node, idx, s, m, ans) + kth(2 * node + 1, idx, m + 1, e, ans);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;

  for (int i = 1; i <= N; i++) {
    cin >> arr[i];
  }

  build(1, 1, N);

  int M;
  cin >> M;

  while (M--) {
    int Q;
    cin >> Q;

    if (Q == 1) {
      int i, j;
      ll k;
      cin >> i >> j >> k;
      range_sum(1, i, j, 1, N, k);
    } else {
      int x;
      cin >> x;
      cout << kth(1, x, 1, N, 0) << '\n';
    }
  }

  return 0;
}
