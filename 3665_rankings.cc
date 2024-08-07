#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

#define MAX_N 505

using namespace std;

bool adj[MAX_N][MAX_N];
int ns[MAX_N];
int in_deg[MAX_N];
bool ranks[MAX_N];
int m, n;

vector<int> ans;
bool vis[MAX_N];

void dfs(int u) {
  vis[u] = true;
  for (int v = 1; v <= n; v++) {
    if (adj[u][v] && !vis[v]) {
      dfs(v);
    }
  }
  ans.push_back(u);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;

  while (T--) {
    memset(adj, false, sizeof(adj));
    memset(ns, 0, sizeof(ns));
    memset(in_deg, 0, sizeof(in_deg));
    memset(ranks, false, sizeof(ranks));

    memset(vis, false, sizeof(vis));
    ans.clear();

    cin >> n;

    for (int i = 1; i <= n; i++) {
      cin >> ns[i];
      int to = ns[i];
      for (int j = 1; j < i; j++) {
        int from = ns[j];
        adj[from][to] = true;
        in_deg[to]++;
      }
    }

    cin >> m;

    for (int i = 0; i < m; i++) {
      int a, b;
      cin >> a >> b;
      if (adj[a][b]) {
        adj[a][b] = false;
        adj[b][a] = true;
        in_deg[a]++;
        in_deg[b]--;
      } else {
        adj[b][a] = false;
        adj[a][b] = true;
        in_deg[b]++;
        in_deg[a]--;
      }
    }

    for (int i = 1; i <= n; i++) {
      if (!vis[i]) {
        dfs(i);
      }
    }
    reverse(ans.begin(), ans.end());

    bool flag = false;
    for (int i = 1; i <= n; i++) {
      int k = in_deg[i];
      if (ranks[k]) {
        flag = true;
        break;
      } else {
        ranks[k] = true;
      }
    }

    if (flag) {
      cout << "IMPOSSIBLE\n";
    } else {
      for (int u : ans) {
        cout << u << ' ';
      }
      cout << '\n';
    }
  }

  return 0;
}
