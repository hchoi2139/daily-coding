#include <algorithm>
#include <cstring>
#include <functional>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

#define MAX_K 5'005
#define MAX_V 10'005

using namespace std;
using pii = pair<int, int>;

vector<int> adj[MAX_V];

stack<int> stk;
bool finished[MAX_V];
int labels[MAX_V];
int label_cnt = 0;

int scc[MAX_V];
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
      scc[p] = scc_cnt;
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

  int k, n, v;
  cin >> k >> n;

  v = 2 * k;

  for (int i = 0; i < n; i++) {
    int l1, l1_rev, l2, l2_rev, l3, l3_rev;
    char c1, c2, c3;
    cin >> l1 >> c1 >> l2 >> c2 >> l3 >> c3;

    if (c1 == 'B') {
      l1_rev = l1 * 2;
      l1 = l1_rev - 1;
    } else {
      l1 *= 2;
      l1_rev = l1 - 1;
    }

    if (c2 == 'B') {
      l2_rev = 2 * l2;
      l2 = l2_rev - 1;
    } else {
      l2 *= 2;
      l2_rev = l2 - 1;
    }

    if (c3 == 'B') {
      l3_rev = 2 * l3;
      l3 = l3_rev - 1;
    } else {
      l3 *= 2;
      l3_rev = l3 - 1;
    }

    adj[l1_rev].push_back(l2);
    adj[l1_rev].push_back(l3);
    adj[l2_rev].push_back(l1);
    adj[l2_rev].push_back(l3);
    adj[l3_rev].push_back(l1);
    adj[l3_rev].push_back(l2);
  }

  for (int i = 1; i <= v; i++) {
    if (!finished[i]) {
      SCC(i);
    }
  }

  for (int i = 2; i <= v; i = i + 2) {
    if (scc[i - 1] == scc[i]) {
      cout << -1;
      return 0;
    }
  }

  vector<pii> ts;

  for (int i = 1; i <= v; i++) {
    ts.push_back(make_pair(scc[i], i));
  }
  sort(ts.begin(), ts.end(), greater<>());

  char ans[MAX_K];
  memset(ans, -1, sizeof ans);

  for (auto [_, cur] : ts) {
    if (ans[(cur + 1) / 2] == -1) {
      ans[(cur + 1) / 2] = (cur % 2 == 0) ? 'B' : 'R';
    }
  }

  for (int i = 1; i <= k; i++) {
    cout << ans[i];
  }

  return 0;
}
