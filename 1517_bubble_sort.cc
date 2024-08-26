#include <iostream>

#define MAX_N 500'005

using namespace std;
using ll = long long;

int arr[MAX_N];
int sorted[MAX_N];
ll ans = 0;

void merge(int l, int m, int r) {
  int a = l;
  int b = m + 1;
  int idx = l;

  while (a <= m && b <= r) {
    if (arr[a] <= arr[b]) {
      sorted[idx] = arr[a];
      a++;
    } else {
      sorted[idx] = arr[b];
      ans += m - a + 1;
      b++;
    }
    idx++;
  }

  while (a <= m) {
    sorted[idx] = arr[a];
    idx++;
    a++;
  }

  while (b <= r) {
    sorted[idx] = arr[b];
    idx++;
    b++;
  }

  for (int i = l; i <= r; i++) {
    arr[i] = sorted[i];
  }
}

void merge_sort(int l, int r) {
  if (l >= r) { return; }
  int m = (l + r) / 2;
  merge_sort(l, m);
  merge_sort(m + 1, r);
  merge(l, m, r);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;

  for (int i = 1; i <= N; i++) {
    cin >> arr[i];
  }

  merge_sort(1, N);

  cout << ans;

  return 0;
}
