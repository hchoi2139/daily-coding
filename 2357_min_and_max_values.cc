#include <algorithm>
#include <iostream>
#include <limits>

#define MAX_N 100'005
#define MAX_M 100'005

using namespace std;

int max_tree[4 * MAX_N];
int min_tree[4 * MAX_N];
int arr[MAX_N];
int N;

void build_aux(int node, int s, int e) {
  if (s == e) {
    max_tree[node] = arr[s];
    min_tree[node] = arr[s];
  } else {
    int m = (s + e) / 2;
    int lt = 2 * node;
    int rt = 2 * node + 1;
    build_aux(lt, s, m);
    build_aux(rt, m + 1, e);
    max_tree[node] = max(max_tree[lt], max_tree[rt]);
    min_tree[node] = min(min_tree[lt], min_tree[rt]);
  }
}

void build() { build_aux(1, 1, N); }

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

int range_min(int l, int r) { return range_min_aux(1, l, r, 1, N); }

int range_max_aux(int node, int l, int r, int s, int e) {
  if (l > e || r < s) {
    return 0;
  }
  if (l <= s && e <= r) {
    return max_tree[node];
  }
  int m = (s + e) / 2;
  int lt = 2 * node;
  int rt = 2 * node + 1;
  return max(range_max_aux(lt, l, r, s, m), range_max_aux(rt, l, r, m + 1, e));
}

int range_max(int l, int r) { return range_max_aux(1, l, r, 1, N); }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int M;
  cin >> N >> M;

  for (int i = 1; i <= N; i++) {
    cin >> arr[i];
  }

  build();

  while (M--) {
    int a, b;
    cin >> a >> b;
    cout << range_min(a, b) << ' ' << range_max(a, b) << '\n';
  }

  return 0;
}
