#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

static constexpr int kMaxLen = 1004;

int dp[kMaxLen][kMaxLen];

string s1;
string s2;

int s1_len;
int s2_len;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> s1 >> s2;
  s1_len = s1.length();
  s2_len = s2.length();

  for (int i = 1; i <= s1_len; i++) {
    for (int j = 1; j <= s2_len; j++) {
      if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  cout << dp[s1_len][s2_len] << '\n';

  string ans;
  int i = s1_len;
  int j = s2_len;

  while (i >= 1 && j >= 1) {
    if (s1[i - 1] == s2[j - 1]) {
      ans.push_back(s1[i - 1]);
      i--;
      j--;
    } else {
      if (dp[i][j] == dp[i - 1][j]) {
        i--;
      } else {
        j--;
      }
    }
  }

  for (int i = ans.size() - 1; i >= 0; i--) {
    cout << ans[i];
  }

  return 0;
}
