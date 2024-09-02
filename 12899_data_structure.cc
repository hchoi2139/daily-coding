#include <iostream>

#define MAX_X 2'000'000

using namespace std;

int tree[4 * MAX_X + 5];

void add(int node, int x, int s, int e) {
  if (x < s || x > e) {
    return;
  }
  tree[node]++;
  if (s == e) {
    return;
  }
  int m = (s + e) / 2;
  int lt = 2 * node;
  int rt = 2 * node + 1;
  add(lt, x, s, m);
  add(rt, x, m + 1, e);
}

int remove(int node, int x, int s, int e) {
  tree[node]--;
  if (s == e) {
    return s;
  }
  int m = (s + e) / 2;
  int lt = 2 * node;
  int rt = 2 * node + 1;
  return (tree[lt] >= x) ? remove(lt, x, s, m)
                         : remove(rt, x - tree[lt], m + 1, e);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;

  while (N--) {
    int T, X;
    cin >> T >> X;

    if (T == 1) {
      add(1, X, 1, MAX_X);
    } else {
      cout << remove(1, X, 1, MAX_X) << '\n';
    }
  }

  return 0;
}
