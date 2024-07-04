#include <algorithm>
#include <iostream>

using namespace std;

static constexpr int kMaxN = 1'000'004;

int arr[kMaxN];
int arr_idx_in_lis[kMaxN];
int lis[kMaxN];

int lis_size;
int arr_size;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> arr_size;

  for (int i = 0; i < arr_size; i++) {
    cin >> arr[i];
  }

  lis[0] = arr[0];
  lis_size++;

  for (int i = 1; i < arr_size; i++) {
    if (lis[lis_size - 1] < arr[i]) {
      lis[lis_size] = arr[i];
      arr_idx_in_lis[i] = lis_size;
      lis_size++;
    }
    else {
      int pos = lower_bound(begin(lis), begin(lis) + lis_size, arr[i]) - begin(lis);
      lis[pos] = arr[i];
      arr_idx_in_lis[i] = pos;
    }
  }

  cout << lis_size << '\n';

  int cur_lis_idx = lis_size - 1;

  for (int i = arr_size - 1; i >= 0; i--) {
    if (arr_idx_in_lis[i] == cur_lis_idx) {
      lis[cur_lis_idx] = arr[i];
      cur_lis_idx--;
    }
  }

  for (int i = 0; i < lis_size; i++) {
    cout << lis[i] << ' ';
  }

  return 0;
}
