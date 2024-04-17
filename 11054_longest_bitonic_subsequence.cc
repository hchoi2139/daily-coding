#include <algorithm>
#include <iostream>
#include <limits>

using namespace std;

static constexpr int kMaxN = 1005;

int lst[kMaxN], memo_left[kMaxN], memo_right[kMaxN];
int n;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  for (int i = 1; i <= n; ++i) {
    cin >> lst[i];
  }

  for (int i = 1; i <= n; ++i) {
    memo_left[i] = 1;
    for (int j = 1; j < i; ++j) {
      if (lst[j] < lst[i]) {
        memo_left[i] = max(memo_left[i], memo_left[j] + 1);
      }
    }
  }

  for (int i = n; i >= 1; --i) {
    memo_right[i] = 1;
    for (int j = n; j > i; --j) {
      if (lst[j] < lst[i]) {
        memo_right[i] = max(memo_right[i], memo_right[j] + 1);
      }
    }
  }

  int res = numeric_limits<int>::min();
  for (int i = 1; i <= n; ++i) {
    res = max(res, memo_left[i] + memo_right[i] - 1);
  }

  cout << res;

  return 0;
}
