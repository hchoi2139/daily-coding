#include <cstring>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using pii = pair<int, int>;

static constexpr int kMaxN = 10'004;
static constexpr int kRootNode = 1;

vector<pii> tree[kMaxN];
bool vis[kMaxN];
int max_dist;
int max_node;

void dfs(int cur, int dist_st_cur) {
  if (vis[cur]) {
    return;
  }

  if (max_dist < dist_st_cur) {
    max_dist = dist_st_cur;
    max_node = cur;
  }

  vis[cur] = true;

  for (const auto& [nxt, dist_cur_nxt] : tree[cur]) {
    dfs(nxt, dist_st_cur + dist_cur_nxt);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  int from;
  int to;
  int dist;

  for (int i = 1; i < n; i++) {
    cin >> from >> to >> dist;
    tree[from].emplace_back(to, dist);
    tree[to].emplace_back(from, dist);
  }

  dfs(kRootNode, 0);

  memset(vis, 0, sizeof vis);
  max_dist = 0;

  dfs(max_node, 0);

  cout << max_dist;

  return 0;
}
