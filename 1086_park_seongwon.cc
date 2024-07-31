#include <iostream>
#include <string>

using namespace std;

using ll = long long;

string ns[16];
int n, k;

int len_ns[16];
int rem_ns[16];
int rem_tens[51];
ll dp[1 << 16][100];

int rem_of(const string& x) {
  int res = 0;
  for (char i : x) {
    res *= 10;
    res += i - '0';
    res %= k;
  }
  return res;
}

ll gcd_of(ll a, ll b) {
  while (b != 0) {
    const ll tmp = b;
    b = a % b;
    a = tmp;
  }
  return a;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> ns[i];
    len_ns[i] = ns[i].size();
  }
  cin >> k;

  for (int i = 0; i < n; i++) {
    rem_ns[i] = rem_of(ns[i]);
  }
  rem_tens[0] = 1 % k;
  for (int i = 1; i <= 50; i++) {
    rem_tens[i] = (rem_tens[i - 1] * 10) % k;
  }

  dp[0][0] = 1;
  for (int cur = 0; cur < (1 << n); cur++) {
    for (int i = 0; i < n; i++) {
      if ((cur & (1 << i)) == 0) {
        const int nxt = cur | (1 << i);
        for (int j = 0; j < k; j++) {
          int nxt_rem = ((j * rem_tens[len_ns[i]]) % k + rem_ns[i]) % k;
          dp[nxt][nxt_rem] += dp[cur][j];
        }
      }
    }
  }

  const ll num = dp[(1 << n) - 1][0];
  ll denom = 1;
  for (int i = 1; i <= n; i++) {
    denom *= i;
  }
  const ll gcd = gcd_of(num, denom);
  cout << num / gcd << '/' << denom / gcd;

  return 0;
}
