#include <iostream>

using namespace std;

using ll = long long;

ll a, b, c;

ll func(ll power) {
  if (power == 1) { return a % c; }

  ll half = func(power / 2) % c;
  ll hh = half * half % c;

  return power % 2 == 0 ? hh : hh * a % c;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> a >> b >> c;
  cout << func(b);

  return 0;
}