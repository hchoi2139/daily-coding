#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

static constexpr int kMaxV = 404;
static constexpr int kInf = 0x3f3f3f3f;

int adj[kMaxV][kMaxV];
int v;
int e;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> v >> e;

  memset(adj, 0x3f, sizeof adj);
  for (int i = 1; i <= v; i++) {
    adj[i][i] = 0;
  }

  int from;
  int to;
  int dist;
  for (int i = 0; i < e; i++) {
    cin >> from >> to >> dist;
    adj[from][to] = dist;
  }

  for (int k = 1; k <= v; k++) {
    for (int i = 1; i <= v; i++) {
      for (int j = 1; j <= v; j++) {
        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
      }
    }
  }

  int res = kInf;
  for (int i = 1; i <= v; i++) {
    for (int j = 1; j <= v; j++) {
      if (i == j)
        continue;
      res = min(res, adj[i][j] + adj[j][i]);
    }
  }

  cout << (res == kInf ? -1 : res);

  return 0;
}
