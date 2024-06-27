#include <cstdio>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;

static constexpr ll kMaxNumVs = 505;
static constexpr ll kMaxNumEs = 6'005;
static constexpr ll kMaxWeight = 10'005;
static constexpr ll kInf = kMaxNumVs * kMaxNumEs * kMaxWeight;

static constexpr int kStartV = 1;

vector<pair<int, ll>> graph[kMaxNumVs];
ll dist[kMaxNumVs];
bool has_neg_cycle = false;

int main() {
  int num_vs;
  int num_es;
  scanf("%d %d", &num_vs, &num_es);

  int from;
  int to;
  ll weight;
  for (int i = 0; i < num_es; i++) {
    scanf("%d %d %lld", &from, &to, &weight);
    graph[from].emplace_back(to, weight);
  }

  for (int i = 1; i <= num_vs; i++) {
    dist[i] = kInf;
  }

  dist[kStartV] = 0;

  for (int i = 1; i <= num_vs; i++) {
    for (int j = 1; j <= num_vs; j++) {
      for (const auto& [nxt, weight] : graph[j]) {
        if (dist[j] != kInf && dist[nxt] > dist[j] + weight) {
          dist[nxt] = dist[j] + weight;
          if (i == num_vs) {
            has_neg_cycle = true;
            break;
          }
        }
      }
    }
  }

  if (has_neg_cycle) {
    printf("-1");
  } else {
    for (int i = 2; i <= num_vs; i++) {
      if (dist[i] == kInf) {
        printf("-1\n");
      } else {
        printf("%lld\n", dist[i]);
      }
    }
  }
}