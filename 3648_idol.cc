#include <algorithm>
#include <cstring>
#include <iostream>
#include <stack>
#include <vector>

#define MAX_N 1'005
#define MAX_V 2'005

using namespace std;

vector<int> adj[MAX_V];

stack<int> stk;
bool finished[MAX_V];
int labels[MAX_V];
int label_cnt;

int scc[MAX_V];
int scc_cnt;

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

  int n, m, v;

  while (cin >> n >> m) {
    v = n * 2;

    for (int i = 0; i < MAX_V; i++) {
      adj[i].clear();
    }

    memset(finished, 0, sizeof finished);
    memset(labels, 0, sizeof labels);
    label_cnt = 0;

    memset(scc, 0, sizeof scc);
    scc_cnt = 0;

    adj[1].push_back(2);

    while (m--) {
      int a, not_a, b, not_b;
      cin >> a >> b;

      if (a > 0) {
        a *= 2;
        not_a = a - 1;
      } else {
        not_a = (-a) * 2;
        a = not_a - 1;
      }

      if (b > 0) {
        b *= 2;
        not_b = b - 1;
      } else {
        not_b = (-b) * 2;
        b = not_b - 1;
      }

      adj[not_a].push_back(b);
      adj[not_b].push_back(a);
    }

    for (int i = 1; i <= v; i++) {
      if (!finished[i]) {
        SCC(i);
      }
    }

    bool is_possible = true;

    for (int i = 2; i <= v; i += 2) {
      if (scc[i - 1] == scc[i]) {
        is_possible = false;
        break;
      }
    }

    cout << (is_possible ? "yes\n" : "no\n");
  }

  return 0;
}
