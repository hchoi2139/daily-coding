#include <iostream>
#include <queue>
#include <vector>

#define MAX_N 32'005

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, M;
  cin >> N >> M;

  vector<int> ords[MAX_N];
  int in_degrees[MAX_N];

  for (int i = 1; i <= M; i++) {
    int A, B;
    cin >> A >> B;
    ords[A].push_back(B);
    in_degrees[B]++;
  }

  priority_queue<int> pq;

  for (int i = 1; i <= N; i++) {
    if (in_degrees[i] == 0) {
      pq.push(-i);
    }
  }

  while (!pq.empty()) {
    int cur = -pq.top();
    pq.pop();

    cout << cur << ' ';

    for (int nxt : ords[cur]) {
      in_degrees[nxt]--;
      if (in_degrees[nxt] == 0) {
        pq.push(-nxt);
      }
    }
  }

  return 0;
}
