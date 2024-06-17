#include <iostream>
#include <stack>
#include <utility>

using namespace std;

using ll = long long;

stack<pair<int, ll>> st;

int num_people;
ll num_visible_pairs;
int cur_height;
ll num_same_height;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> num_people;

  cin >> cur_height;
  st.emplace(cur_height, 1);

  for (int i = 1; i < num_people; i++) {
    cin >> cur_height;
    num_same_height = 1;

    while (!st.empty() && st.top().first < cur_height) {
      num_visible_pairs += st.top().second;
      st.pop();
    }

    if (!st.empty()) {
      if (st.top().first == cur_height) {
        num_visible_pairs += st.top().second;
        if (st.size() > 1) {
          num_visible_pairs++;
        }
        num_same_height += st.top().second;
        st.pop();
      } else {
        num_visible_pairs++;
      }
    }

    st.emplace(cur_height, num_same_height);
  }

  cout << num_visible_pairs;

  return 0;
}