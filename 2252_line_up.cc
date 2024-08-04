#include <algorithm>
#include <iostream>
#include <vector>

#define MAX_N 32'005

using namespace std;

vector<int> adj[MAX_N];
bool vis[MAX_N];
vector<int> ans;
int n, m;

void dfs(int u) {
  vis[u] = true;
  for (int v : adj[u]) {
    if (!vis[v]) {
      dfs(v);
    }
  }
  ans.push_back(u);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
  }

  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      dfs(i);
    }
  }
  reverse(ans.begin(), ans.end());

  for (int u : ans) {
    cout << u << ' ';
  }
  
  return 0;
}
