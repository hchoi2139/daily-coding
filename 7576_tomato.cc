#include <algorithm>
#include <iostream>
#include <queue>

static constexpr int kMaxNumRows = 1005;
static constexpr int kMaxNumCols = 1005;

using namespace std;

queue<pair<int, int>> q;

int dr[] = { 0, 0, -1, 1 };
int dc[] = { 1, -1, 0, 0 };

int box[kMaxNumRows][kMaxNumCols];
int num_rows;
int num_cols;

[[nodiscard]] inline bool is_inside_the_box(int r, int c) {
  return 0 <= r && r < num_rows && 0 <= c && c < num_cols;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> num_cols >> num_rows;

  for (int i = 0; i < num_rows; i++) {
    for (int j = 0; j < num_cols; j++) {
      cin >> box[i][j];
      if (box[i][j] == 1) {
        q.emplace(i, j);
      }
    }
  }

  while (!q.empty()) {
    auto cur = q.front();
    q.pop();

    for (int i = 0; i < 4; i++) {
      int nr = cur.first + dr[i];
      int nc = cur.second + dc[i];
      if (is_inside_the_box(nr, nc) && box[nr][nc] == 0) {
        box[nr][nc] = box[cur.first][cur.second] + 1;
        q.emplace(nr, nc);
      }
    }
  }

  int res = -1;

  for (int i = 0; i < num_rows; i++) {
    for (int j = 0; j < num_cols; j++) {
      if (box[i][j] == 0) {
        cout << "-1";
        return 0;
      }
      res = max(res, box[i][j] - 1);
    }
  }

  cout << res;

  return 0;
}