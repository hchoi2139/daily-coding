#include <algorithm>
#include <iostream>
#include <stack>

using ll = long long;

static constexpr int kMaxN = 100005;

ll hs[kMaxN];

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  while (true) {
    int num_recs;
    std::cin >> num_recs;
    if (num_recs == 0) {
      break;
    }

    for (int i = 0; i < num_recs; ++i) {
      std::cin >> hs[i];
    }

    std::stack<int> stack;
    ll max_area = -1;

    for (int i = 0; i < num_recs; ++i) {
      while (!stack.empty() && hs[i] < hs[stack.top()]) {
        ll h_top = hs[stack.top()];
        ll w = i;
        stack.pop();

        if (!stack.empty()) {
          w = i - stack.top() - 1;
        }

        max_area = std::max(max_area, w * h_top);
      }
      stack.push(i);
    }

    while (!stack.empty()) {
      ll h_top = hs[stack.top()];
      ll w = num_recs;
      stack.pop();

      if (!stack.empty()) {
        w = num_recs - stack.top() - 1;
      }

      max_area = std::max(max_area, w * h_top);
    }

    std::cout << max_area << '\n';
  }

  return 0;
}