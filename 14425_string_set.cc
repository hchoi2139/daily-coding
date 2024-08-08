#include <iostream>
#include <string>

using namespace std;

struct Trie {
  Trie *children[26];
  bool is_end;

  Trie() : children(), is_end(false) {}

  void Insert(string &key, size_t idx) {
    if (idx == key.length())
      is_end = true;
    else {
      int nxt = key[idx] - 'a';
      if (children[nxt] == nullptr) {
        children[nxt] = new Trie();
      }
      children[nxt]->Insert(key, idx + 1);
    }
  }

  bool Find(string &key, size_t idx) {
    if (idx == key.length()) {
      return is_end;
    }
    int nxt = key[idx] - 'a';
    return children[nxt] ? children[nxt]->Find(key, idx + 1) : false;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  Trie root;
  size_t N, M;
  cin >> N >> M;

  for (size_t i = 0; i < N; i++) {
    string word;
    cin >> word;
    root.Insert(word, 0);
  }

  int cnt = 0;
  for (size_t i = 0; i < M; i++) {
    string word;
    cin >> word;
    if (root.Find(word, 0)) {
      cnt++;
    }
  }

  cout << cnt;

  return 0;
}
