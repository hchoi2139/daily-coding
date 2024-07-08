#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

static constexpr int kMaxN = 1'004;

struct Coord {
  int r;
  int c;
};

inline int l1_dist(const Coord& c1, const Coord& c2) {
  return abs(c1.r - c2.r) + abs(c1.c - c2.c);
}

Coord cases[kMaxN];
int dp[kMaxN][kMaxN];
int n;
int w;

int dfs(const int p1, const int p2) {
  if (p1 == w || p2 == w) {
    return 0;
  }

  if (dp[p1][p2] != -1) {
    return dp[p1][p2];
  }

  int nxt = max(p1, p2) + 1;

  int dist1;
  int dist2;

  if (p1 == 0) {
    dist1 = l1_dist({ 1, 1 }, cases[nxt]);
  } else {
    dist1 = l1_dist(cases[p1], cases[nxt]);
  }

  if (p2 == 0) {
    dist2 = l1_dist({ n, n }, cases[nxt]);
  } else {
   dist2 = l1_dist(cases[p2], cases[nxt]);
  }

  int rem_p1 = dist1 + dfs(nxt, p2);
  int rem_p2 = dist2 + dfs(p1, nxt);
  dp[p1][p2] = min(rem_p1, rem_p2);

  return dp[p1][p2];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  cin >> w;

  int r;
  int c;

  for (int i = 1; i <= w; i++) {
    cin >> r >> c;
    cases[i] = { r, c };
  }

  memset(dp, -1, sizeof dp);

  cout << dfs(0, 0) << '\n';

  // Track the route of two police cars.

  int p1 = 0;
  int p2 = 0;

  while (p1 != w && p2 != w) {
    int nxt = max(p1, p2) + 1;
    int dist1;
    int dist2;

    if (p1 == 0) {
      dist1 = l1_dist({ 1, 1 }, cases[nxt]);
    } else {
      dist1 = l1_dist(cases[p1], cases[nxt]);
    }

    if (p2 == 0) {
      dist2 = l1_dist({ n, n }, cases[nxt]);
    } else {
      dist2 = l1_dist(cases[p2], cases[nxt]);
    }

    int rem_p1 = dist1 + dp[nxt][p2];
    int rem_p2 = dist2 + dp[p1][nxt];

    if (rem_p1 < rem_p2) {
      cout << 1 << '\n';
      p1 = nxt;
    } else {
      cout << 2 << '\n';
      p2 = nxt;
    }
  }

  return 0;
}
