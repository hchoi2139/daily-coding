#include <iostream>

#define MAX_N 1'000'005
#define MOD 1'000'000'007

using namespace std;
using ll = long long;

ll tree[4 * MAX_N];
ll arr[MAX_N];
int N;

void build_aux(int node, int s, int e) {
  if (s == e) {
    tree[node] = arr[s];
  } else {
    int m = (s + e) / 2;
    int lt = 2 * node;
    int rt = 2 * node + 1;
    build_aux(lt, s, m);
    build_aux(rt, m + 1, e);
    tree[node] = tree[lt] * tree[rt] % MOD;
  }
}

void build() { build_aux(1, 1, N); }

ll prod_aux(int node, int l, int r, int s, int e) {
  if (l > e || r < s) {
    return 1;
  }
  if (l <= s && e <= r) {
    return tree[node];
  }
  int m = (s + e) / 2;
  int lt = 2 * node;
  int rt = 2 * node + 1;
  return prod_aux(lt, l, r, s, m) * prod_aux(rt, l, r, m + 1, e) % MOD;
}

ll prod(int l, int r) { return prod_aux(1, l, r, 1, N); }

void update_aux(int node, int idx, ll new_val, int s, int e) {
  if (s == e) {
    tree[node] = new_val;
  } else {
    int m = (s + e) / 2;
    int lt = 2 * node;
    int rt = 2 * node + 1;
    if (idx <= m) {
      update_aux(lt, idx, new_val, s, m);
    } else {
      update_aux(rt, idx, new_val, m + 1, e);
    }
    tree[node] = tree[lt] * tree[rt] % MOD;
  }
}

void update(int idx, int new_val) {
  update_aux(1, idx, new_val, 1, N);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int M, K;
  cin >> N >> M >> K;

  for (int i = 1; i <= N; i++) {
    cin >> arr[i];
  }

  build();

  for (int i = 0; i < M + K; i++) {
    int a, b, c;
    cin >> a >> b >> c;

    if (a == 1) {
      update(b, c);
    } else {
      cout << prod(b, c) << '\n';
    }
  }

  return 0;
}
