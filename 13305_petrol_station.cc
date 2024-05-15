#include <algorithm>
#include <iostream>

using namespace std;

using ll = long long;

static constexpr ll kMaxNumCities = 100005;

ll roads[kMaxNumCities], prices[kMaxNumCities];

int num_cities;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> num_cities;

  for (int i = 0; i < num_cities - 1; ++i) {
    cin >> roads[i];
  }

  for (int i = 0; i < num_cities; ++i) {
    cin >> prices[i];
  }

  ll cur_price = prices[0];
  ll tot_price = cur_price * roads[0];

  for (int i = 1; i < num_cities - 1; ++i) {
    cur_price = min(cur_price, prices[i]);
    tot_price += cur_price * roads[i];
  }

  cout << tot_price;

  return 0;
}