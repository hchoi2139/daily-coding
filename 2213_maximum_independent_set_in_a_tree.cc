#include <algorithm>
#include <iostream>
#include <vector>

static constexpr int kMaxN = 10'004;
static constexpr int kInclude = 1;
static constexpr int kExclude = 0;
static constexpr int kRoot = 1;
static constexpr int kParentOfRoot = 0;

std::vector<int> tree[kMaxN];
std::vector<int> mis;
bool is_in_mis[kMaxN];
int dp[kMaxN][2];
int ws[kMaxN];
int n;

void find(const int cur, const int prev) {
  dp[cur][kInclude] = ws[cur];
  dp[cur][kExclude] = 0;
  for (const int nxt : tree[cur]) {
    if (nxt != prev) {
      find(nxt, cur);
      dp[cur][kInclude] += dp[nxt][kExclude];
      dp[cur][kExclude] += std::max(dp[nxt][kInclude], dp[nxt][kExclude]);
    }
  }
}

void trace(const int cur, const int prev) {
  if (!is_in_mis[prev] && dp[cur][kInclude] > dp[cur][kExclude]) {
    mis.push_back(cur);
    is_in_mis[cur] = true;
  }
  for (const int nxt : tree[cur]) {
    if (nxt != prev) {
      trace(nxt, cur);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;

  for (int i = 1; i <= n; i++) {
    std::cin >> ws[i];
  }

  int a, b;
  for (int i = 1; i < n; i++) {
    std::cin >> a >> b;
    tree[a].push_back(b);
    tree[b].push_back(a);
  }

  find(kRoot, kParentOfRoot);

  trace(kRoot, kParentOfRoot);
  std::sort(mis.begin(), mis.end());

  std::cout << std::max(dp[kRoot][kInclude], dp[kRoot][kExclude]) << '\n';
  for (const int node : mis) {
    std::cout << node << ' ';
  }

  return 0;
}
