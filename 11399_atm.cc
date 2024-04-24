#include <algorithm>
#include <functional>
#include <iostream>

static constexpr int kMaxN = 1005;

int n, lst[kMaxN];

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    std::cin >> lst[i];
  }

  std::sort(lst, lst + n, std::less<>());

  int time_waited = 0;
  int res = 0;
  
  for (int i = 0; i < n; ++i) {
    res += time_waited + lst[i];
    time_waited += lst[i];
  }

  std::cout << res;

  return 0;
}
