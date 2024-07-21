#include <algorithm>
#include <iostream>

using namespace std;

static constexpr int kMaxNumPoints = 500'004;

int parent[kMaxNumPoints];
int m;
int n;

[[nodiscard]] int find_parent(const int x) {
  if (parent[x] != x) {
    parent[x] = find_parent(parent[x]);
  }
  return parent[x];
}

void make_union(const int x, const int y) {
  const int px = find_parent(x);
  const int py = find_parent(y);
  parent[max(px, py)] = min(px, py);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  for (int i = 0; i < n; i++) {
    parent[i] = i;
  }

  int a;
  int b;

  for (int turn = 1; turn <= m; turn++) {
    cin >> a >> b;

    if (find_parent(a) == find_parent(b)) {
      cout << turn;
      return 0;
    }

    make_union(a, b);
  }

  cout << 0;

  return 0;
}
