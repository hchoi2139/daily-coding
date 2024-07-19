#include <iostream>
#include <algorithm>

using namespace std;

static constexpr int kMaxN = 204;

int parent[kMaxN];
int m;
int n;

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

  for (int i = 1; i <= n; i++) {
    parent[i] = i;
  }

  int is_connected = 0;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> is_connected;

      if (is_connected == 1) {
        union_parent(i, j);
      }
    }
  }

  int root;
  int city;

  cin >> city;
  root = find_parent(city);

  for (int i = 1; i < m; i++) {
    cin >> city;
    
    if (find_parent(root) != find_parent(city)) {
      cout << "NO";
      return 0;
    }
  }

  cout << "YES";

  return 0;
}
