#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

static constexpr int kMaxSLen = 1000005;

std::string s, bomb;
int bomb_size;

char stk[kMaxSLen];
int stk_top = -1;
int stk_size = 0;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> s >> bomb;
  bomb_size = bomb.length();

  for (const char c : s) {
    stk_top++;
    stk_size++;
    stk[stk_top] = c;

    bool contains_bomb = true;

    if (stk_size >= bomb_size) {
      for (int i = bomb_size - 1; i >= 0; i--) {
        if (bomb[i] != stk[i + stk_size - bomb_size]) {
          contains_bomb = false;
          break;
        }
      }

      if (contains_bomb) {
        stk_top -= bomb_size;
        stk_size -= bomb_size;
      }
    }
  }

  if (stk_size == 0) {
    std::cout << "FRULA";
  } else {
    std::ostringstream osstream;
    for (int i = 0; i < stk_size; i++) {
      osstream << stk[i];
    }
    std::cout << osstream.str();
  }

  return 0;
}