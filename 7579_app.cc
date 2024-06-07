#include <algorithm>
#include <iostream>

static constexpr int kMaxNumApps = 105;
static constexpr int kMaxCostOfAnApp = 105;
static constexpr int kMaxTotalCostOfApps = kMaxCostOfAnApp * kMaxNumApps;

int dp[kMaxNumApps][kMaxTotalCostOfApps];
int mems[kMaxNumApps];
int costs[kMaxNumApps];

int num_apps, tar_mem, tot_cost;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> num_apps >> tar_mem;

  for (int i = 1; i <= num_apps; i++) {
    std::cin >> mems[i];
  }

  for (int i = 1; i <= num_apps; i++) {
    std::cin >> costs[i];
    tot_cost += costs[i];
  }

  for (int a = 1; a <= num_apps; a++) {
    for (int c = 0; c < costs[a]; c++) {
      dp[a][c] = dp[a - 1][c];
    }
    for (int c = costs[a]; c <= tot_cost; c++) {
      dp[a][c] = std::max({
          dp[a][c],
          dp[a - 1][c],
          dp[a - 1][c - costs[a]] + mems[a],
      });
    }
  }

  for (int c = 0; c <= tot_cost; c++) {
    if (dp[num_apps][c] >= tar_mem) {
      std::cout << c;
      break;
    }
  }

  return 0;
}