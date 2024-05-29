#include <algorithm>
#include <iostream>

static constexpr int kMaxN = 100005;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int arr[kMaxN];
  int n, m;

  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  std::sort(arr, arr + n);

  std::cin >> m;

  for (int i = 0; i < m; ++i) {
    int target;
    std::cin >> target;

    std::cout << (std::binary_search(arr, arr + n, target) ? 1 : 0) << '\n';
  }

  return 0;
}