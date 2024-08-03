#include <cassert>
#include <iostream>
#include <string>

#define MAX_L 1'000'005

using namespace std;

string s;
int l;

int fail[MAX_L];

void find_fail() {
  int m = s.length();
  int j = 0;
  for (int i = 1; i < m; i++) {
    while (j > 0 && s[i] != s[j]) {
      j = fail[j - 1];
    }
    if (s[i] == s[j]) {
      j++;
      fail[i] = j;
    } else {
      fail[i] = 0;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> l >> s;

  find_fail();

  cout << l - fail[l - 1];

  return 0;
}
