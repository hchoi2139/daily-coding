#include <iostream>

#define MAX_M 200'005
#define MAX_DIGITS_N 19

using namespace std;

int tbl[MAX_M][MAX_DIGITS_N];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int m;
  cin >> m;

  for (int i = 1; i <= m; i++) {
    cin >> tbl[i][0];
  }

  for (int j = 1; j < MAX_DIGITS_N; j++) {
    for (int i = 1; i <= m; i++) {
      tbl[i][j] = tbl[tbl[i][j - 1]][j - 1];
    }
  }

  int Q;
  cin >> Q;

  while (Q--) {
    int n, x;
    cin >> n >> x;
    
    for (int i = 0; n != 0; i++, n >>= 1) {
      if (n % 2 == 1) {
        x = tbl[x][i];
      }
    }

    cout << x << '\n';
  }

  return 0;
}
