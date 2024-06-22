#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

static constexpr int kMaxV = 20005;
static constexpr int kMaxE = 200005;

static constexpr int kRed = 1;
static constexpr int kBlack = 2;

using namespace std;

vector<int> graph[kMaxV];
int vis[kMaxV];
int k, v, e, from, to;

void dfs(const int cur) {
  for (int nxt : graph[cur]) {
    if (!vis[nxt]) {
      vis[nxt] = (vis[cur] == kRed) ? kBlack : kRed;
      dfs(nxt);
    }
  }
}

bool is_bipartite_graph() {
  for (int cur = 1; cur <= v; cur++) {
    for (int nxt : graph[cur]) {
      if (vis[cur] == vis[nxt]) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  scanf("%d", &k);

  while (k--) {
    scanf("%d %d", &v, &e);

    for (int i = 0; i < e; i++) {
      scanf("%d %d", &from, &to);
      graph[from].push_back(to);
      graph[to].push_back(from);
    }

    for (int i = 1; i <= v; i++) {
      if (!vis[i]) {
        vis[i] = kRed;
        dfs(i);
      }
    }

    is_bipartite_graph() ? printf("YES\n") : printf("NO\n");

    for (int i = 1; i <= v; i++) {
      graph[i].clear();
    }
    memset(vis, 0, sizeof(int) * (v + 1));
  }

  return 0;
}