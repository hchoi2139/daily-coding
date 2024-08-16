#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

#define MAX_N 100'005
#define MAX_DIGITS_N 17

using namespace std;
using pii = pair<int, int>;

vector<pii> adj[MAX_N];
int N;

int parent[MAX_N][MAX_DIGITS_N];
int min_rd[MAX_N][MAX_DIGITS_N];
int max_rd[MAX_N][MAX_DIGITS_N];
int depth[MAX_N];

void DFS(int prv, int cur) {
  for (auto [nxt, len] : adj[cur]) {
    if (nxt != prv) {
      parent[nxt][0] = cur;
      min_rd[nxt][0] = len;
      max_rd[nxt][0] = len;
      depth[nxt] = depth[cur] + 1;
      DFS(cur, nxt);
    }
  }
}

pii LCA(int x, int y) {
  if (depth[x] > depth[y]) {
    swap(x, y);
  }

  int cur_min = numeric_limits<int>::max();
  int cur_max = 0;
  int dif = depth[y] - depth[x];

  for (int i = 0; dif != 0; i++, dif >>= 1) {
    if (dif % 2 == 1) {
      cur_min = min(cur_min, min_rd[y][i]);
      cur_max = max(cur_max, max_rd[y][i]);
      y = parent[y][i];
    }
  }

  if (x == y) {
    return {cur_min, cur_max};
  }

  for (int k = MAX_DIGITS_N - 1; k >= 0; k--) {
    if (parent[x][k] != 0 && parent[x][k] != parent[y][k]) {
      cur_min = min({cur_min, min_rd[x][k], min_rd[y][k]});
      cur_max = max({cur_max, max_rd[x][k], max_rd[y][k]});
      x = parent[x][k];
      y = parent[y][k];
    }
  }
  cur_min = min({cur_min, min_rd[x][0], min_rd[y][0]});
  cur_max = max({cur_max, max_rd[x][0], max_rd[y][0]});

  return {cur_min, cur_max};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N;

  for (int i = 1; i < N; i++) {
    int A, B, C;
    cin >> A >> B >> C;
    adj[A].emplace_back(B, C);
    adj[B].emplace_back(A, C);
  }

  DFS(0, 1);

  for (int j = 1; j < MAX_DIGITS_N; j++) {
    for (int i = 1; i <= N; i++) {
      parent[i][j] = parent[parent[i][j - 1]][j - 1];
      min_rd[i][j] = min(min_rd[i][j - 1], min_rd[parent[i][j - 1]][j - 1]);
      max_rd[i][j] = max(max_rd[i][j - 1], max_rd[parent[i][j - 1]][j - 1]);
    }
  }

  int K;
  cin >> K;

  while (K--) {
    int D, E;
    cin >> D >> E;
    auto [min_rd_len, max_rd_len] = LCA(D, E);
    cout << min_rd_len << ' ' << max_rd_len << '\n';
  }

  return 0;
}
