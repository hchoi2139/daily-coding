#include <iostream>

using namespace std;

static constexpr int kMaxN = 100005;

int lst[kMaxN], prefix_sum[kMaxN];
int n, m;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    cin >> lst[i];
  }

  prefix_sum[0] = 0;
  prefix_sum[1] = lst[1];
  for (int i = 2; i <= n; ++i) {
    prefix_sum[i] = prefix_sum[i - 1] + lst[i];
  }

  int start, end;
  for (int i = 0; i < m; ++i) {
    cin >> start >> end;
    cout << prefix_sum[end] - prefix_sum[start - 1] << '\n';
  }

  return 0;
}
