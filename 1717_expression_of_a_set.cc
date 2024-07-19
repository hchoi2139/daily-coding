#include <algorithm>
#include <iostream>

using namespace std;

static constexpr int kMaxN = 1'000'004;

int parent[kMaxN];
int n, m;

[[nodiscard]] int find_parent(const int x) {
  if (parent[x] != x) {
    parent[x] = find_parent(parent[x]);
  }
  return parent[x];
}

void union_parent(const int x, const int y) {
  const int px = find_parent(x);
  const int py = find_parent(y);
  parent[max(px, py)] = min(px, py);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  for (int i = 0; i <= n; i++) {
    parent[i] = i;
  }

  int op;
  int a;
  int b;

  for (int i = 0; i < m; i++) {
    cin >> op >> a >> b;

    if (op == 0) {
      union_parent(a, b);
    } else {
      find_parent(a) == find_parent(b) ? (cout << "YES\n") : (cout << "NO\n");
    }
  }

  return 0;
}
