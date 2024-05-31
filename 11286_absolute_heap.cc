#include <iostream>
#include <queue>
#include <vector>

int n;

struct Cmp {
  bool operator()(int a, int b) {
    if (std::abs(a) == std::abs(b)) {
      return a > b;
    }
    return std::abs(a) > std::abs(b);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;

  std::priority_queue<int, std::vector<int>, Cmp> pq;

  for (int i = 0; i < n; i++) {
    int val;
    std::cin >> val;

    if (val == 0) {
      if (pq.empty()) {
        std::cout << "0\n";
      } else {
        std::cout << pq.top() << '\n';
        pq.pop();
      }
    } else {
      pq.push(val);
    }
  }

  return 0;
}