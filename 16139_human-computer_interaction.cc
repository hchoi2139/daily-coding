#include <iostream>
#include <string>

static constexpr int kNumOfAlphabets = 26;
static constexpr int kMaxQ = 200005;

int cnts[kNumOfAlphabets][kMaxQ];

std::string str;
char target;
int q, start, end;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> str >> q;

  cnts[str[0] - 'a'][0] = 1;

  for (size_t i = 1; i < str.size(); ++i) {
    for (auto& cnt : cnts) {
      cnt[i] = cnt[i - 1];
    }
    cnts[str[i] - 'a'][i] += 1;
  }

  for (int i = 0; i < q; ++i) {
    std::cin >> target >> start >> end;
    int res = (start == 0)
                  ? cnts[target - 'a'][end]
                  : cnts[target - 'a'][end] - cnts[target - 'a'][start - 1];
    std::cout << res << '\n';
  }

  return 0;
}
