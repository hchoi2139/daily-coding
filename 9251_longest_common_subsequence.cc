#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

static constexpr int kMaxStrLen = 1005;

string a, b;
int memo[kMaxStrLen][kMaxStrLen];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> a >> b;

  int len_a = a.length();
  int len_b = b.length();

  for (int i = 1; i <= len_a; ++i) {
    for (int j = 1; j <= len_b; ++j) {
      if (a[i - 1] == b[j - 1]) {
        memo[i][j] = memo[i - 1][j - 1] + 1;
      } else {
        memo[i][j] = max(memo[i - 1][j], memo[i][j - 1]);
      }
    }
  }

  cout << memo[len_a][len_b];

  return 0;
}
