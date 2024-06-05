#include <cstdlib>
#include <iostream>

static constexpr int kMaxNumWeights = 35;
static constexpr int kMaxNumBeads = 12;

static constexpr int kMaxBeadWeight = 40005;

bool dp[kMaxBeadWeight];
int weights[kMaxNumWeights];

int num_weights, num_beads;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> num_weights;

  int sum_weights = 0;

  for (int i = 0; i < num_weights; i++) {
    std::cin >> weights[i];
    sum_weights += weights[i];
  }

  dp[0] = true;
  
  for (int i = 0; i < num_weights; i++) {
    for (int j = sum_weights; j >= 0; j--) {
      if (dp[j]) {
        dp[j + weights[i]] = true;
      }
    }
    for (int j = 0; j <= sum_weights; j++) {
      if (dp[j]) {
        dp[std::abs(j - weights[i])] = true;
      }
    }
  }

  std::cin >> num_beads;

  for (int i = 0; i < num_beads; i++) {
    int tmp;
    std::cin >> tmp;
    std::cout << (dp[tmp] ? "Y " : "N ");
  }

  return 0;
}