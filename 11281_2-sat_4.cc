#include <algorithm>
#include <cstring>
#include <functional>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

#define MAX_N 10'005
#define MAX_V 20'005

using namespace std;
using pii = pair<int, int>;

vector<int> adj[MAX_V];

stack<int> stk;
int labels[MAX_V];
int label_cnt = 0;
bool finished[MAX_V];

int sccs[MAX_V];
int scc_cnt = 0;

int SCC(int cur) {
  label_cnt++;
  labels[cur] = label_cnt;
  int parent = label_cnt;
  stk.push(cur);

  for (int nxt : adj[cur]) {
    if (labels[nxt] == 0) {
      parent = min(parent, SCC(nxt));
    } else if (!finished[nxt]) {
      parent = min(parent, labels[nxt]);
    }
  }

  if (labels[cur] == parent) {
    scc_cnt++;
    while (!stk.empty()) {
      int p = stk.top();
      stk.pop();
      finished[p] = true;
      sccs[p] = scc_cnt;
      if (p == cur) {
        break;
      }
    }
  }

  return parent;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, M, V;
  cin >> N >> M;

  V = N * 2;

  while (M--) {
    int x, not_x, y, not_y;
    cin >> x >> y;

    if (x > 0) {
      x *= 2;
      not_x = x - 1;
    } else {
      not_x = (-x) * 2;
      x = not_x - 1;
    }

    if (y > 0) {
      y *= 2;
      not_y = y - 1;
    } else {
      not_y = (-y) * 2;
      y = not_y - 1;
    }

    adj[not_x].push_back(y);
    adj[not_y].push_back(x);
  }

  for (int i = 1; i <= V; i++) {
    if (!finished[i]) {
      SCC(i);
    }
  }

  for (int i = 2; i <= V; i += 2) {
    if (sccs[i - 1] == sccs[i]) {
      cout << 0;
      return 0;
    }
  }

  cout << 1 << '\n';

  vector<pii> ts;

  for (int i = 1; i <= V; i++) {
    ts.push_back(make_pair(sccs[i], i));
  }
  sort(ts.begin(), ts.end(), greater<>());

  int ans[MAX_N];
  memset(ans, -1, sizeof ans);

  for (auto [_, cur] : ts) {
    if (ans[(cur + 1) / 2] == -1) {
      ans[(cur + 1) / 2] = (cur % 2 == 0) ? 0 : 1;
    }
  }

  for (int i = 1; i <= N; i++) {
    cout << ans[i] << ' ';
  }
  cout << '\n';

  return 0;
}
