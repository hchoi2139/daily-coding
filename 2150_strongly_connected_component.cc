#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

#define MAX_V 10'005

using namespace std;

vector<int> adj[MAX_V];
int V, E;

stack<int> stk;
bool finished[MAX_V];
int labels[MAX_V];
int label;

vector<vector<int>> ans;

int SCC(int cur) {
  label++;
  int parent = label;
  labels[cur] = label;
  stk.push(cur);

  for (int nxt : adj[cur]) {
    if (labels[nxt] == 0) {
      parent = min(parent, SCC(nxt));
    } else if (!finished[nxt]) {
      parent = min(parent, labels[nxt]);
    }
  }

  if (parent == labels[cur]) {
    vector<int> scc_set;
    while (!stk.empty()) {
      int p = stk.top();
      stk.pop();
      scc_set.push_back(p);
      finished[p] = true;
      if (p == cur) {
        break;
      }
    }
    sort(scc_set.begin(), scc_set.end());
    ans.push_back(scc_set);
  }

  return parent;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> V >> E;

  for (int i = 0; i < E; i++) {
    int A, B;
    cin >> A >> B;
    adj[A].push_back(B);
  }

  for (int i = 1; i <= V; i++) {
    if (labels[i] == 0) {
      SCC(i);
    }
  }

  sort(ans.begin(), ans.end(),
       [](vector<int> &a, vector<int> &b) { return a[0] < b[0]; });

  cout << ans.size() << '\n';

  for (auto &v : ans) {
    for (int a : v) {
      cout << a << ' ';
    }
    cout << -1 << '\n';
  }

  return 0;
}
