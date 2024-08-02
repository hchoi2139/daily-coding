#include <iostream>
#include <string>
#include <vector>

using namespace std;

string t, p;
int n, m;

vector<int> pi;
vector<int> ans;

void find_pi() {
  pi.resize(m, 0);
  for (int i = 1; i < m; i++) {
    int j = pi[i - 1];
    while (j > 0 && p[i] != p[j]) {
      j = pi[j - 1];
    }
    if (p[i] == p[j]) {
      j++;
    }
    pi[i] = j;
  }
}

void kmp() {
  int j = 0;
  for (int i = 0; i < n; i++) {
    while (j > 0 && t[i] != p[j]) {
      j = pi[j - 1];
    }
    if (t[i] == p[j]) {
      if (j == m - 1) {
        ans.push_back(i - m + 1);
        j = pi[j];
      } else {
        j++;
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  getline(cin, t);
  getline(cin, p);

  n = (int)t.length();
  m = (int)p.length();

  if (m > n) {
    cout << 0;
    return 0;
  }

  find_pi();
  kmp();

  cout << ans.size() << '\n';
  for (int i : ans) {
    cout << i + 1 << ' ';
  }

  return 0;
}
