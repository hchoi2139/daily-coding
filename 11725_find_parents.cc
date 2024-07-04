#include <iostream>
#include <queue>

using namespace std;

static constexpr int kMaxN = 100'004;
static constexpr int kRoot = 1;

vector<int> tree[kMaxN];
int parent[kMaxN];
queue<int> q;
int n;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  int x;
  int y;
  for (int i = 1; i < n; i++) {
    cin >> x >> y;
    tree[x].push_back(y);
    tree[y].push_back(x);
  }

  q.push(kRoot);

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (int nxt : tree[cur]) {
      if (parent[nxt] != 0 || nxt == kRoot) {
        continue;
      }
      parent[nxt] = cur;
      q.push(nxt);
    }
  }

  for (int i = 2; i <= n; i++) {
    cout << parent[i] << '\n';
  }

  return 0;
}
