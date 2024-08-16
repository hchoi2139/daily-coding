#include <algorithm>
#include <cstring>
#include <iostream>
#include <stack>
#include <vector>

#define MAX_N 100'005

using namespace std;

vector<int> adj[MAX_N];
int N;

stack<int> stk;
bool finished[MAX_N];
int labels[MAX_N];
int label_cnt;

int in_degs[MAX_N];
int sccs[MAX_N];
int scc_cnt;

vector<int> ans;

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

  if (parent == labels[cur]) {
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

  int T;
  cin >> T;

  while (T--) {
    for (int i = 0; i < N; i++) {
      adj[i].clear();
    }

    memset(finished, 0, sizeof finished);
    memset(labels, 0, sizeof labels);
    label_cnt = 0;

    memset(in_degs, 0, sizeof in_degs);
    memset(sccs, 0, sizeof sccs);
    scc_cnt = 0;

    ans.clear();

    int M;
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
      int A, B;
      cin >> A >> B;
      adj[A].push_back(B);
    }

    for (int i = 0; i < N; i++) {
      if (!finished[i]) {
        SCC(i);
      }
    }

    for (int u = 0; u < N; u++) {
      for (int v : adj[u]) {
        if (sccs[u] != sccs[v]) {
          in_degs[sccs[v]]++;
        }
      }
    }

    int num_zero_in_degs = 0;
    for (int i = 1; i <= scc_cnt; i++) {
      if (in_degs[i] == 0) {
        num_zero_in_degs++;
      }
    }

    if (num_zero_in_degs == 1) {
      for (int i = 0; i < N; i++) {
        if (in_degs[sccs[i]] == 0) {
          ans.push_back(i);
        }
      }
      sort(ans.begin(), ans.end());
      for (int k : ans) {
        cout << k << '\n';
      }
    } else {
      cout << "Confused\n";
    }

    cout << '\n';
  }

  return 0;
}
