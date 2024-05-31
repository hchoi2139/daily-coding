#include <algorithm>
#include <iostream>

using ll = long long;

static constexpr size_t kMaxNumTrees = 1000005;

int tree_hts[kMaxNumTrees];
int num_trees, tar_tree_len;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> num_trees >> tar_tree_len;

  int max_tree_ht = -1;

  for (int i = 0; i < num_trees; ++i) {
    std::cin >> tree_hts[i];
    max_tree_ht = std::max(max_tree_ht, tree_hts[i]);
  }

  int lo = 0;
  int hi = max_tree_ht;
  int ans = -1;

  while (lo <= hi) {
    int mid = ((lo ^ hi) >> 1) + (lo & hi);

    ll tot_tree_cut_len = 0;
    for (int i = 0; i < num_trees; ++i) {
      tot_tree_cut_len += std::max(0, tree_hts[i] - mid);
    }

    if (tot_tree_cut_len >= tar_tree_len) {
      ans = std::max(ans, mid);
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }

  std::cout << ans;

  return 0;
}