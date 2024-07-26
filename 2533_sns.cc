#include <iostream>
#include <vector>

static constexpr int kMaxN = 1'000'004;

static constexpr int kRoot = 1;
static constexpr int kParentOfRoot = -1;

static constexpr int kIsEA = 1;
static constexpr int kIsNotEA = 0;

std::vector<int> tree[kMaxN];
int dp[kMaxN][2];
int n;

void DFS(const int cur, const int prev) {
  dp[cur][kIsEA] = 1;
  for (const int nxt : tree[cur]) {
    if (nxt == prev) {
      continue;
    }
    DFS(nxt, cur);
    // If cur is early adapter, it has the luxury to cherry pick its nxts that
    // makes the number of early adapters the least.
    dp[cur][kIsEA] += std::min(dp[nxt][kIsEA], dp[nxt][kIsNotEA]);
    // If cur is not early adapter, then its nxts must all be early adapters.
    dp[cur][kIsNotEA] += dp[nxt][kIsEA];
  }
}

void Input() {
  std::cin >> n;

  for (int i = 1; i < n; i++) {
    int u, v;
    std::cin >> u >> v;
    tree[u].push_back(v);
    tree[v].push_back(u);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Input();
  DFS(kRoot, kParentOfRoot);

  std::cout << std::min(dp[kRoot][kIsEA], dp[kRoot][kIsNotEA]);

  return 0;
}
