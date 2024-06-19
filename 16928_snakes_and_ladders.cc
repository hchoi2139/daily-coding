#include <iostream>
#include <queue>

static constexpr int kMaxMapSize = 105;
static constexpr int kInitPos = 1;
static constexpr int kFinPos = 100;

using namespace std;

queue<int> q;

int map[kMaxMapSize];
int vis[kMaxMapSize];
int num_ladders;
int num_snakes;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> num_ladders >> num_snakes;

  for (int i = 0; i < num_ladders; i++) {
    int x, y;
    cin >> x >> y;
    map[x] = y;
  }

  for (int i = 0; i < num_snakes; i++) {
    int u, v;
    cin >> u >> v;
    map[u] = v;
  }

  q.push(kInitPos);

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (int i = 1; i <= 6; i++) {
      int nxt = cur + i;
      if (nxt == kFinPos) {
        cout << vis[cur] + 1;
        return 0;
      }
      if (nxt < kFinPos) {
        while (map[nxt] != 0) {
          nxt = map[nxt];
        }
        if (vis[nxt] == 0) {
          q.push(nxt);
          vis[nxt] = vis[cur] + 1;
        }
      }
    }
  }

  return 0;
}