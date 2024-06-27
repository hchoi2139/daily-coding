#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

static constexpr int kMaxNumInts = 2'005;
static constexpr int kMaxNumRoads = 50'005;
static constexpr int kMaxDistOfARoad = 1'000;
static constexpr int kInf = kMaxNumRoads * kMaxDistOfARoad;

using namespace std;

using pii = pair<int, int>;

vector<pii> graph[kMaxNumInts];
int cands[kMaxNumInts];
int dist_start[kMaxNumInts];
int dist_far[kMaxNumInts];
int num_cands;
int start;
int one_end;
int other_end;
int close;
int far;

void init() {
  int num_ints;
  int num_roads;
  scanf("%d %d %d", &num_ints, &num_roads, &num_cands);

  for (int i = 1; i <= num_ints; i++) {
    graph[i].clear();
    cands[i] = 0;
    dist_start[i] = kInf;
    dist_far[i] = kInf;
  }

  scanf("%d %d %d", &start, &one_end, &other_end);

  int from;
  int to;
  int dist_from_to;
  for (int i = 0; i < num_roads; i++) {
    scanf("%d %d %d", &from, &to, &dist_from_to);
    graph[from].emplace_back(to, dist_from_to);
    graph[to].emplace_back(from, dist_from_to);
  }

  for (int i = 1; i <= num_cands; i++) {
    scanf("%d", &cands[i]);
  }
  std::sort(cands + 1, cands + num_cands + 1);
}

void find_shortest_path(const int st, int (&dist)[kMaxNumInts]) {
  priority_queue<pii> pq;
  dist[st] = 0;
  pq.emplace(0, st);

  while (!pq.empty()) {
    auto [dist_st_cur, cur] = pq.top();
    dist_st_cur = -dist_st_cur;
    pq.pop();

    if (dist[cur] < dist_st_cur) {
      continue;
    }

    for (const auto& [nxt, dist_cur_nxt] : graph[cur]) {
      int dist_st_nxt = dist_st_cur + dist_cur_nxt;
      if (dist[nxt] > dist_st_nxt) {
        dist[nxt] = dist_st_nxt;
        pq.emplace(-dist_st_nxt, nxt);
      }
    }
  }
}

int main() {
  int num_tests;
  scanf("%d", &num_tests);

  while (num_tests--) {
    init();

    find_shortest_path(start, dist_start);

    if (dist_start[one_end] < dist_start[other_end]) {
      close = one_end;
      far = other_end;
    } else {
      close = other_end;
      far = one_end;
    }

    int dist_close_far;
    for (const auto& [nxt, dist_close_nxt] : graph[close]) {
      if (nxt == far) {
        dist_close_far = dist_close_nxt;
      }
    }

    find_shortest_path(far, dist_far);

    for (int i = 1; i <= num_cands; i++) {
      int cand = cands[i];
      if (dist_start[cand] ==
          dist_start[close] + dist_close_far + dist_far[cand]) {
        printf("%d ", cand);
      }
    }
    printf("\n");
  }
}