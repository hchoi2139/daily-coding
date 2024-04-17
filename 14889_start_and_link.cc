#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>

using namespace std;

static constexpr int MAX_N = 23;

int abilities[MAX_N][MAX_N];
bool team_alloc[MAX_N];
int n, min_diff = numeric_limits<int>::max();

void dfs(int cnt, int start_pos) {
  if (cnt == n / 2) {
    int start = 0;
    int link = 0;
    
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (team_alloc[i] && team_alloc[j]) { start += abilities[i][j]; }
        if (!team_alloc[i] && !team_alloc[j]) { link += abilities[i][j]; }
      }
    }

    min_diff = min(min_diff, abs(start - link));
    return;
  }

  for (int i = start_pos; i <= n; ++i) {
    team_alloc[i] = true;
    dfs(cnt + 1, i + 1);
    team_alloc[i] = false;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      cin >> abilities[i][j];
    }
  }

  dfs(0, 1);

  cout << min_diff << endl;
  return 0;
}
