#include <cstring>
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

static constexpr int kInf = 200'001;
static constexpr int kUnvisited = -1;

stack<int> st;
queue<int> q;
int dp[kInf];
int n;
int k;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k;

  if (n == k) {
    cout << 0 << '\n' << n;;
    return 0;
  }

  memset(dp, kUnvisited, sizeof dp);
  dp[n] = 0;

  q.push(n);

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    if (cur == k) {
      break;
    }

    if (cur * 2 < kInf && dp[cur * 2] == kUnvisited) {
      q.push(cur * 2);
      dp[cur * 2] = dp[cur] + 1;
    }

    if (cur + 1 < kInf && dp[cur + 1] == kUnvisited) {
      q.push(cur + 1);
      dp[cur + 1] = dp[cur] + 1;
    }

    if (cur - 1 >= 0 && dp[cur - 1] == kUnvisited) {
      q.push(cur - 1);
      dp[cur - 1] = dp[cur] + 1;
    }
  }

  cout << dp[k] << '\n';

  int cur = k;
  st.push(cur);

  while (cur != n) {
    if (cur + 1 < kInf && dp[cur + 1] == dp[cur] - 1) {
      cur += 1;
    } else if (cur - 1 >= 0 && dp[cur - 1] == dp[cur] - 1) {
      cur -= 1;
    } else {
      cur /= 2;
    }
    st.push(cur);
  }

  while (!st.empty()) {
    cout << st.top() << ' ';
    st.pop();
  }

  return 0;
}
