#include <cstring>
#include <iostream>
#include <vector>

#define MAX_N 10'005

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;

  vector<int> x_parents;
  vector<int> y_parents;
  int parent[MAX_N];

  while (T--) {
    memset(parent, 0, sizeof(parent));
    x_parents.clear();
    y_parents.clear();

    int N;
    cin >> N;

    for (int i = 1; i < N; i++) {
      int A, B;
      cin >> A >> B;
      parent[B] = A;
    }

    int x, y;
    cin >> x >> y;

    while (x != 0) {
      x_parents.push_back(x);
      x = parent[x];
    }

    while (y != 0) {
      y_parents.push_back(y);
      y = parent[y];
    }

    int x_idx = x_parents.size() - 1;
    int y_idx = y_parents.size() - 1;

    while (x_idx >= 0 && y_idx >= 0 && x_parents[x_idx] == y_parents[y_idx]) {
      x_idx--;
      y_idx--;
    }

    cout << x_parents[x_idx + 1] << '\n';
  }

  return 0;
}
