#include <cmath>
#include <iostream>

static constexpr int kNumStats = 8;

double stats[kNumStats];
double perm[kNumStats];
bool vis[kNumStats];
int num_convex_polygons = 0;

bool IsConvex() {
  for (int i = 0; i < kNumStats; i++) {
    const double a = perm[i];
    const double b = perm[(i + 1) % kNumStats];
    const double c = perm[(i + 2) % kNumStats];
    if (b * (a + c) < std::sqrt(2) * a * c) {
      return false;
    }
  }
  return true;
}

void DFS(const int cnt) {
  if (cnt == kNumStats) {
    num_convex_polygons += (IsConvex() ? 1 : 0);
  }
  for (int i = 0; i < kNumStats; i++) {
    if (vis[i]) {
      continue;
    }
    vis[i] = true;
    perm[cnt] = stats[i];
    DFS(cnt + 1);
    vis[i] = false;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  for (auto& stat : stats) {
    std::cin >> stat;
  }

  DFS(0);

  std::cout << num_convex_polygons;

  return 0;
}
