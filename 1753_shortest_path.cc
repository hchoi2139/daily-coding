#include <cstdio>
#include <functional>
#include <iterator>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

static constexpr int kMaxV = 20005;
static constexpr int kInf = std::numeric_limits<int>::max();

using namespace std;

using pii = pair<int, int>;

vector<pii> graph[kMaxV];
priority_queue<pii, vector<pii>, greater<>> pq;
int dist[kMaxV];

int num_vertices;
int num_arcs;
int start;
int from;
int to;
int weight;

int main() {
  // Input
  scanf("%d %d", &num_vertices, &num_arcs);
  scanf("%d", &start);

  for (int i = 0; i < num_arcs; i++) {
    scanf("%d %d %d", &from, &to, &weight);
    graph[from].emplace_back(to, weight);
  }

  // Dijkstra's algorithm
  fill_n(begin(dist) + 1, num_vertices, kInf);
  dist[start] = 0;
  pq.emplace(0, start);

  while (!pq.empty()) {
    const auto [dist_start_to_cur, cur] = pq.top();
    pq.pop();

    for (const auto &[nxt, dist_cur_to_nxt] : graph[cur]) {
      int alt_dist_start_to_nxt = dist_start_to_cur + dist_cur_to_nxt;
      if (alt_dist_start_to_nxt < dist[nxt]) {
        dist[nxt] = alt_dist_start_to_nxt;
        pq.emplace(alt_dist_start_to_nxt, nxt);
      }
    }
  }

  // Output
  for (int i = 1; i <= num_vertices; i++) {
    dist[i] == kInf ? printf("INF\n") : printf("%d\n", dist[i]);
  }

  return 0;
}