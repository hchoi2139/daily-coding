#include <cstring>
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

static constexpr int kUpperBound = 10'000;
static constexpr int kMaxInt = 9'999;

inline int op_d(const int in) {
  return 2 * in % kUpperBound;
}

inline int op_s(const int in) {
  return (in + kMaxInt) % kUpperBound;
}

inline int op_l(const int in) {
  return (in % 1'000) * 10 + (in / 1'000);
}

inline int op_r(const int in) {
  return (in % 10) * 1'000 + (in / 10);
}

int dp[kUpperBound];
int int_trace[kUpperBound];
char op_trace[kUpperBound];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  while (t--) {
    int a;
    int b;
    cin >> a >> b;

    memset(dp, -1, sizeof dp);
    memset(int_trace, -1, sizeof(int_trace));

    queue<int> q;

    dp[a] = 0;
    q.push(a);

    while (!q.empty()) {
      int cur = q.front();
      q.pop();

      if (cur == b) {
        break;
      }

      int nxt_d = op_d(cur);
      int nxt_s = op_s(cur);
      int nxt_l = op_l(cur);
      int nxt_r = op_r(cur);

      if (dp[nxt_d] == -1) {
        dp[nxt_d] = dp[cur] + 1;
        q.push(nxt_d);
        int_trace[nxt_d] = cur;
        op_trace[nxt_d] = 'D';
      }
      if (dp[nxt_s] == -1) {
        dp[nxt_s] = dp[cur] + 1;
        q.push(nxt_s);
        int_trace[nxt_s] = cur;
        op_trace[nxt_s] = 'S';
      }
      if (dp[nxt_l] == -1) {
        dp[nxt_l] = dp[cur] + 1;
        q.push(nxt_l);
        int_trace[nxt_l] = cur;
        op_trace[nxt_l] = 'L';
      }
      if (dp[nxt_r] == -1) {
        dp[nxt_r] = dp[cur] + 1;
        q.push(nxt_r);
        int_trace[nxt_r] = cur;
        op_trace[nxt_r] = 'R';
      }
    }

    stack<char> st;
    int cur = b;

    while (cur != a) {
      st.push(op_trace[cur]);
      cur = int_trace[cur];
    }

    while (!st.empty()) {
      cout << st.top();
      st.pop();
    }

    cout << '\n';
  }

  return 0;
}
