#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

#define MAX_N 1'000'005

using namespace std;
using pii = pair<int, int>;

vector<pii> lines;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;

  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    lines.push_back(make_pair(x, y));
  }

  sort(lines.begin(), lines.end());

  int l = numeric_limits<int>::min();
  int r = numeric_limits<int>::min();
  int ans = 0;

  for (int i = 0; i < N; i++) {
    pii p = lines[i];
    if (r < p.first) {
      ans += r - l;
      l = p.first;
      r = p.second;
    } else {
      r = max(r, p.second);
    }
  }

  ans += r - l;

  cout << ans;

  return 0;
}
