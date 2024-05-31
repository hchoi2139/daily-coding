#include <iostream>

static constexpr int kMaxN = 1000005;

int lis[kMaxN];
int n, lis_len = 0;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;

  std::cin >> lis[0];
  lis_len++;

  for (int i = 1; i < n; i++) {
    int elem;
    std::cin >> elem;

    if (elem > lis[lis_len - 1]) {
      lis[lis_len] = elem;
      lis_len++;
    } else {
      int lo = 0;
      int hi = lis_len - 1;

      while (lo <= hi) {
        int mid = (lo + hi) / 2;
        
        if (elem > lis[mid]) {
          lo = mid + 1;
        } else {
          hi = mid - 1;
        }
      }

      lis[lo] = elem;
    }
  }

  std::cout << lis_len;

  return 0;
}