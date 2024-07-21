#include <iostream>
#include <vector>

using namespace std;

static constexpr int kMaxN = 100'004;

vector<int> tree[kMaxN];
int sizes[kMaxN];
int n, r, q;

void dfs(const int cur, const int parent) {
  for (int child : tree[cur]) {
    if (child != parent) {
      dfs(child, cur);
    }
  }
  
  if (parent != -1) {
    sizes[parent] += sizes[cur];
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> r >> q;

  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    tree[u].push_back(v);
    tree[v].push_back(u);
  }

  for (int i = 1; i <= n; i++) {
    sizes[i] = 1;
  }

  dfs(r, -1);

  for (int i = 0; i < q; i++) {
    int u;
    cin >> u;
    cout << sizes[u] << '\n';
  }

  return 0;
}
