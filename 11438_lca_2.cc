#include <iostream>
#include <vector>

#define MAX_N 100'005
#define MAX_DIGITS_N 17

using namespace std;

vector<int> adj[MAX_N];
int N;

int parent[MAX_N][MAX_DIGITS_N];
int depth[MAX_N];

void FindDepth(int prev, int cur) {
  for (int nxt : adj[cur]) {
    if (prev != nxt) {
      depth[nxt] = depth[cur] + 1;
      FindDepth(cur, nxt);
    }
  }
}

void FindDirectParent(int prev, int cur) {
  for (int nxt : adj[cur]) {
    if (prev != nxt) {
      parent[nxt][0] = cur;
      FindDirectParent(cur, nxt);
    }
  }
}

void FindParent() {
  FindDirectParent(0, 1);
  for (int j = 1; j < MAX_DIGITS_N; j++) {
    for (int i = 1; i <= N; i++) {
      parent[i][j] = parent[parent[i][j - 1]][j - 1];
    }
  }
}

int LCA(int x, int y) {
  if (depth[x] > depth[y]) {
    swap(x, y);
  }

  int dif = depth[y] - depth[x];
  
  for (int i = 0; dif != 0; i++, dif >>= 1) {
    if (dif % 2 == 1) {
      y = parent[y][i];
    }
  }

  if (x == y) {
    return x;
  }

  for (int k = MAX_DIGITS_N - 1; k >= 0; k--) {
    if (parent[x][k] != 0 && parent[x][k] != parent[y][k]) {
      x = parent[x][k];
      y = parent[y][k];
    }
  }

  return parent[x][0];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N;

  for (int i = 1; i < N; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  FindDepth(0, 1);
  FindParent();

  int M;
  cin >> M;

  while (M--) {
    int x, y;
    cin >> x >> y;
    cout << LCA(x, y) << '\n';
  }

  return 0;
}
