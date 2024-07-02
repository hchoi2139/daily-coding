#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

constexpr int kMaxN = 32;

ll objs[kMaxN];
size_t n;
ll cap;

void dfs(size_t lo, size_t hi, vector<ll>& v, ll sum) {
  if (lo > hi) {
    v.push_back(sum);
    return;
  }
  dfs(lo + 1, hi, v, sum);
  dfs(lo + 1, hi, v, sum + objs[lo]);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> cap;

  for (size_t i = 1; i <= n; i++) {
    cin >> objs[i];
  }

  vector<ll> l_sums;
  vector<ll> r_sums;

  dfs(1, n / 2, l_sums, 0);
  dfs(n / 2 +1, n, r_sums, 0);

  sort(r_sums.begin(), r_sums.end());

  size_t cnt = 0;
  for (ll l_sum : l_sums) {
    cnt += upper_bound(r_sums.begin(), r_sums.end(), cap - l_sum) - r_sums.begin();
  }

  cout << cnt;

  return 0;
}
