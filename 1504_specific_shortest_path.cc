#include <algorithm>
#include <cstdio>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

using pii = pair<int, int>;

static constexpr int kMaxV = 805;
static constexpr int kInf = 200000005;

vector<pii> graph[kMaxV];
priority_queue<pii, vector<pii>, greater<>> pq;
int dist[kMaxV];
int num_vs;
int num_es;
int a, b, c, v1, v2;
int start_v, end_v;

void find_shortest_path(int st) {
  fill_n(dist + 1, num_vs, kInf);
  dist[st] = 0;
  pq.emplace(0, st);

  while (!pq.empty()) {
    const auto [dist_st_cur, cur] = pq.top();
    pq.pop();

    for (const auto& [nxt, dist_cur_nxt] : graph[cur]) {
      int alt_dist_st_nxt = dist_st_cur + dist_cur_nxt;
      if (alt_dist_st_nxt < dist[nxt]) {
        dist[nxt] = alt_dist_st_nxt;
        pq.emplace(alt_dist_st_nxt, nxt);
      }
    }
  }
}

int main() {
  scanf("%d %d", &num_vs, &num_es);

  for (int i = 0; i < num_es; i++) {
    scanf("%d %d %d", &a, &b, &c);
    graph[a].emplace_back(b, c);
    graph[b].emplace_back(a, c);
  }

  scanf("%d %d", &v1, &v2);

  start_v = 1;
  end_v = num_vs;

  find_shortest_path(v1);
  int dist_start_v1 = dist[start_v];
  int dist_v1_v2 = dist[v2];
  int dist_v1_end = dist[end_v];

  find_shortest_path(v2);
  int dist_start_v2 = dist[start_v];
  int dist_v2_v1 = dist_v1_v2;
  int dist_v2_end = dist[end_v];

  int ans = min(dist_start_v1 + dist_v1_v2 + dist_v2_end,
                dist_start_v2 + dist_v2_v1 + dist_v1_end);
  ans < kInf ? printf("%d", ans) : printf("-1");

  return 0;
}