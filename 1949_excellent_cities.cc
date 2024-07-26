#include <algorithm>
#include <iostream>
#include <vector>

static constexpr int kMaxN = 10'004;

static constexpr int kRoot = 1;
static constexpr int kParentOfRoot = -1;

static constexpr int kIsExcellent = 1;
static constexpr int kIsNotExcellent = 0;

std::vector<int> tree[kMaxN];
int dp[kMaxN][2];
int pops[kMaxN];
int n;

void Input() {
  std::cin >> n;

  for (int i = 1; i <= n; i++) {
    std::cin >> pops[i];
  }

  for (int i = 1; i < n; i++) {
    int a, b;
    std::cin >> a >> b;
    tree[a].push_back(b);
    tree[b].push_back(a);
  }
}

void DFS(const int cur, const int prev) {
  dp[cur][kIsExcellent] = pops[cur];
  for (const int nxt : tree[cur]) {
    if (nxt == prev) {
      continue;
    }
    DFS(nxt, cur);
    dp[cur][kIsExcellent] += dp[nxt][kIsNotExcellent];
    dp[cur][kIsNotExcellent] += std::max(dp[nxt][kIsExcellent], dp[nxt][kIsNotExcellent]);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Input();
  DFS(kRoot, kParentOfRoot);

  std::cout << std::max(dp[kRoot][kIsExcellent], dp[kRoot][kIsNotExcellent]);

  return 0;
}
