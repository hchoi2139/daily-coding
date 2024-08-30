#include <algorithm>
#include <cstring>
#include <iostream>
#include <limits>

#define MAX_N 100'005

using namespace std;

int min_tree[4 * MAX_N];
int max_tree[4 * MAX_N];
int arr[MAX_N];
int N;

void build_aux(int node, int s, int e) {
  if (s == e) {
    min_tree[node] = s;
    max_tree[node] = s;
  } else {
    int m = (s + e) / 2;
    int lt = 2 * node;
    int rt = 2 * node + 1;
    build_aux(lt, s, m);
    build_aux(rt, m + 1, e);
    min_tree[node] = min(min_tree[lt], min_tree[rt]);
    max_tree[node] = max(max_tree[lt], max_tree[rt]);
  }
}

void build() { build_aux(1, 0, N - 1); }

int range_min_aux(int node, int l, int r, int s, int e) {
  if (l > e || r < s) {
    return numeric_limits<int>::max();
  }
  if (l <= s && e <= r) {
    return min_tree[node];
  }
  int m = (s + e) / 2;
  int lt = 2 * node;
  int rt = 2 * node + 1;
  return min(range_min_aux(lt, l, r, s, m), range_min_aux(rt, l, r, m + 1, e));
}

int range_min(int l, int r) { return range_min_aux(1, l, r, 0, N - 1); }

int range_max_aux(int node, int l, int r, int s, int e) {
  if (l > e || r < s) {
    return numeric_limits<int>::min();
  }
  if (l <= s && e <= r) {
    return max_tree[node];
  }
  int m = (s + e) / 2;
  int lt = 2 * node;
  int rt = 2 * node + 1;
  return max(range_max_aux(lt, l, r, s, m), range_max_aux(rt, l, r, m + 1, e));
}

int range_max(int l, int r) { return range_max_aux(1, l, r, 0, N - 1); }

void update_aux(int node, int idx, int new_val, int s, int e) {
  if (s == e) {
    min_tree[node] = new_val;
    max_tree[node] = new_val;
    arr[s] = new_val;
  } else {
    int m = (s + e) / 2;
    int lt = 2 * node;
    int rt = 2 * node + 1;
    if (idx <= m) {
      update_aux(lt, idx, new_val, s, m);
    } else {
      update_aux(rt, idx, new_val, m + 1, e);
    }
    min_tree[node] = min(min_tree[lt], min_tree[rt]);
    max_tree[node] = max(max_tree[lt], max_tree[rt]);
  }
}

void update(int idx, int new_val) { update_aux(1, idx, new_val, 0, N - 1); }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;

  while (T--) {
    int K;
    cin >> N >> K;

    memset(min_tree, 0, sizeof min_tree);
    memset(max_tree, 0, sizeof max_tree);
    for (int i = 0; i < N; i++) {
      arr[i] = i;
    }

    build();

    while (K--) {
      int Q, A, B;
      cin >> Q >> A >> B;

      if (Q == 0) {
        int val_A = arr[A];
        int val_B = arr[B];
        update(A, val_B);
        update(B, val_A);
      } else {
        int min_AB = range_min(A, B);
        int max_AB = range_max(A, B);
        cout << (min_AB == A && max_AB == B ? "YES" : "NO") << '\n';
      }
    }
  }

  return 0;
}
