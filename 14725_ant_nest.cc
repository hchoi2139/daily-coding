#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct TrieNode {
  map<string, TrieNode*> children;

  explicit TrieNode() {}

  void Insert(vector<string>& v, int idx) {
    if (idx == (int)v.size()) {
      return;
    }
    if (children.find(v[idx]) == children.end()) {
      children[v[idx]] = new TrieNode();
    }
    children[v[idx]]->Insert(v, idx + 1);
  }

  void Print(int depth) {
    for (auto& child : children) {
      for (int i = 0; i < depth; i++) {
        cout << "--";
      }
      cout << child.first << '\n';
      child.second->Print(depth + 1);
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;

  TrieNode* root = new TrieNode();

  vector<string> foods;

  for (int i = 0; i < N; i++) {
    int K;
    cin >> K;
    foods.resize(K);
    for (int i = 0; i < K; i++) {
      cin >> foods[i];
    }
    root->Insert(foods, 0);
  }

  root->Print(0);

  return 0;
}
