#include <cstring>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using pii = pair<int, int>;

static constexpr int kMaxV = 100'004;

vector<pii> tree[kMaxV];
bool vis[kMaxV];
int num_nodes;
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

  cin >> num_nodes;

  int from;
  int to;
  int dist;

  for (int i = 1; i <= num_nodes; i++) {
    cin >> from;

    while (true) {
      cin >> to;
      if (to == -1) {
        break;
      }
      cin >> dist;
      tree[from].emplace_back(to, dist);
    }
  }

  dfs(1, 0);

  memset(vis, 0, sizeof vis);
  max_dist = 0;

  dfs(max_node, 0);

  cout << max_dist;

  return 0;
}
