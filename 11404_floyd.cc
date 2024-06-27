#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

static constexpr int kMaxNumVs = 104;
static constexpr int kInf = 0x3f3f3f3f;

int dist[kMaxNumVs][kMaxNumVs];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int num_vs;
  int num_es;
  cin >> num_vs >> num_es;

  memset(dist, 0x3f, sizeof(dist));
  for (int i = 1; i <= num_vs; i++) {
    dist[i][i] = 0;
  }

  int from;
  int to;
  int weight;
  for (int i = 1; i <= num_es; i++) {
    cin >> from >> to >> weight;
    // There may exist multiple routes between from and to while having
    // different weights.
    dist[from][to] = min(dist[from][to], weight);
  }

  for (int k = 1; k <= num_vs; k++) {
    for (int i = 1; i <= num_vs; i++) {
      for (int j = 1; j <= num_vs; j++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }

  for (int i = 1; i <= num_vs; i++) {
    for (int j = 1; j <= num_vs; j++) {
      if (dist[i][j] == kInf) {
        cout << 0 << ' ';
      } else {
        cout << dist[i][j] << ' ';
      }
    }
    cout << '\n';
  }
}