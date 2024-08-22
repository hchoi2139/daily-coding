#include <algorithm>
#include <iostream>

#define MAX_N 1'000'005

using namespace std;
using ll = long long;

ll tree[4 * MAX_N];
ll ns[MAX_N];
int N, M, K;

void build(int v, int tl, int tr) {
  if (tl == tr) {
    tree[v] = ns[tl];
  } else {
    int tm = (tl + tr) / 2;
    build(v * 2, tl, tm);
    build(v * 2 + 1, tm + 1, tr);
    tree[v] = tree[v * 2] + tree[v * 2 + 1];
  }
}

ll sum(int v, int tl, int tr, int l, int r) {
  if (l > r)
    return 0;
  if (l == tl && r == tr) {
    return tree[v];
  }
  int tm = (tl + tr) / 2;
  return sum(v * 2, tl, tm, l, min(r, tm)) +
         sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
}

void update(int v, int tl, int tr, int pos, ll new_val) {
  if (tl == tr) {
    tree[v] = new_val;
  } else {
    int tm = (tl + tr) / 2;
    if (pos <= tm)
      update(v * 2, tl, tm, pos, new_val);
    else
      update(v * 2 + 1, tm + 1, tr, pos, new_val);
    tree[v] = tree[v * 2] + tree[v * 2 + 1];
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> M >> K;

  for (int i = 0; i < N; i++) {
    cin >> ns[i];
  }

  build(1, 0, N - 1);

  for (int i = 0; i < M + K; i++) {
    int a, b;
    ll c;
    cin >> a >> b >> c;

    if (a == 1)
      update(1, 0, N - 1, b - 1, c);
    else
      cout << sum(1, 0, N - 1, b - 1, c - 1) << '\n';
  }

  return 0;
}
