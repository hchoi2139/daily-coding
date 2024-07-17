#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> pre;

void pre_to_post(const int lo, const int hi) {
  if (lo > hi) {
    return;
  }

  const int root = pre[lo];
  const int pivot = upper_bound(pre.begin() + lo + 1, pre.begin() + hi + 1, root) - pre.begin();

  pre_to_post(lo + 1, pivot - 1);
  pre_to_post(pivot, hi);
  cout << root << '\n';
}

int main() {
  int key;

  while (cin >> key) {
    pre.push_back(key);
  }

  pre_to_post(0, pre.size() - 1);

  return 0;
}
