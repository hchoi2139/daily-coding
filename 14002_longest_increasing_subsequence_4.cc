#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

static constexpr int kMaxN = 1'004;

stack<int> stk;

int arr[kMaxN];
int dp[kMaxN];

int lis_last_idx;
int lis_len;
int n;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
  }

  for (int i = 1; i <= n; i++) {
    dp[i] = 1;

    for (int j = 1; j < i; j++) {
      if (arr[j] < arr[i]) {
        dp[i] = max(dp[i], dp[j] + 1);
      }
    }

    if (dp[i] > lis_len) {
      lis_last_idx = i;
      lis_len = dp[i];
    }
  }

  cout << lis_len << '\n';

  stk.push(arr[lis_last_idx]);
  int cur_idx = lis_last_idx;

  for (int i = lis_last_idx - 1; i > 0; i--) {
    if (arr[i] < arr[cur_idx] && dp[i] + 1 == dp[cur_idx]) {
      cur_idx = i;
      stk.push(arr[i]);
    }
  }

  while (!stk.empty()) {
    cout << stk.top() << ' ';
    stk.pop();
  }

  return 0;
}
