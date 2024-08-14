#include <cstring>
#include <iostream>
#include <stack>
#include <vector>

#define MAX_N 100'005

using namespace std;

vector<int> adj[MAX_N];
int N, M;

stack<int> stk;
bool finished[MAX_N];
int labels[MAX_N];
int label_cnt;

int in_degs[MAX_N];
int scc_ids[MAX_N];
int scc_id;

int SCC(int cur) {
  label_cnt++;
  int parent = label_cnt;
  labels[cur] = label_cnt;
  stk.push(cur);

  for (int nxt : adj[cur]) {
    if (labels[nxt] == 0) {
      parent = min(parent, SCC(nxt));
    } else if (!finished[nxt]) {
      parent = min(parent, labels[nxt]);
    }
  }

  if (parent == labels[cur]) {
    scc_id++;
    while (!stk.empty()) {
      int p = stk.top();
      stk.pop();
      finished[p] = true;
      scc_ids[p] = scc_id;
      if (p == cur)
        break;
    }
  }

  return parent;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;

  while (T--) {
    for (int i = 0; i < MAX_N; i++) {
      adj[i].clear();
    }

    memset(finished, 0, sizeof finished);
    memset(labels, 0, sizeof labels);
    label_cnt = 0;

    memset(in_degs, 0, sizeof in_degs);
    memset(scc_ids, 0, sizeof scc_ids);
    scc_id = 0;

    cin >> N >> M;

    for (int i = 0; i < M; i++) {
      int x, y;
      cin >> x >> y;
      adj[x].push_back(y);
    }

    for (int i = 1; i <= N; i++) {
      if (!finished[i]) {
        SCC(i);
      }
    }

    for (int u = 1; u <= N; u++) {
      for (int v : adj[u]) {
        if (scc_ids[u] != scc_ids[v]) {
          in_degs[scc_ids[v]]++;
        }
      }
    }

    int ans = 0;

    for (int i = 1; i <= scc_id; i++) {
      if (in_degs[i] == 0) {
        ans++;
      }
    }

    cout << ans << '\n';
  }

  return 0;
}
