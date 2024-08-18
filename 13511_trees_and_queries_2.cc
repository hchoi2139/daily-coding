#include <iostream>
#include <utility>
#include <vector>

#define MAX_N 100'005
#define MAX_DIGITS_N 17

using namespace std;

using ll = long long;

vector<pair<int, ll>> adj[MAX_N];
int N;

int parent[MAX_N][MAX_DIGITS_N];
ll cost[MAX_N][MAX_DIGITS_N];
int depth[MAX_N];

void DFS(int prv, int cur) {
  for (auto [nxt, w] : adj[cur]) {
    if (nxt != prv) {
      parent[nxt][0] = cur;
      cost[nxt][0] = w;
      depth[nxt] = depth[cur] + 1;
      DFS(cur, nxt);
    }
  }
}

pair<int, ll> LCA(int x, int y) {
  if (depth[x] > depth[y]) {
    swap(x, y);
  }

  int dif = depth[y] - depth[x];
  ll tot_cost = 0;

  for (int i = 0; dif != 0; i++, dif >>= 1) {
    if (dif % 2 == 1) {
      tot_cost += cost[y][i];
      y = parent[y][i];
    }
  }

  if (x == y) {
    return {x, tot_cost};
  }

  for (int k = MAX_DIGITS_N - 1; k >= 0; k--) {
    if (parent[x][k] != 0 && parent[x][k] != parent[y][k]) {
      tot_cost += cost[x][k] + cost[y][k];
      x = parent[x][k];
      y = parent[y][k];
    }
  }

  tot_cost += cost[x][0] + cost[y][0];
  x = parent[x][0];

  return {x, tot_cost};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;

  for (int i = 1; i < N; i++) {
    int u, v;
    ll w;
    cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  // Assume the root node is 1.
  DFS(0, 1);

  for (int j = 1; j < MAX_DIGITS_N; j++) {
    for (int i = 1; i <= N; i++) {
      parent[i][j] = parent[parent[i][j - 1]][j - 1];
      cost[i][j] = cost[i][j - 1] + cost[parent[i][j - 1]][j - 1];
    }
  }

  int M;
  cin >> M;

  while (M--) {
    int q;
    cin >> q;

    if (q == 1) {
      int u, v;
      cin >> u >> v;

      auto [_, c] = LCA(u, v);

      cout << c << '\n';
    } else {
      int u, v, k;
      cin >> u >> v >> k;

      auto [a, _] = LCA(u, v);

      if (depth[u] - depth[a] >= k - 1) {
        int dif = k - 1;

        for (int i = 0; dif != 0; i++, dif >>= 1) {
          if (dif % 2 == 1) {
            u = parent[u][i];
          }
        }

        cout << u << '\n';
      } else {
        int dif = (depth[u] - depth[a]) + (depth[v] - depth[a]) - (k - 1);

        for (int i = 0; dif != 0; i++, dif >>= 1) {
          if (dif % 2 == 1) {
            v = parent[v][i];
          }
        }

        cout << v << '\n';
      }
    }
  }

  return 0;
}
