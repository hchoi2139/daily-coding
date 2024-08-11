#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Trie {
  unordered_map<char, Trie *> children;
  bool is_end;

  Trie() : is_end(false){};

  void Insert(string &key) {
    Trie *cur = this;
    for (size_t i = 0; i < key.length(); i++) {
      if (!cur->children[key[i]]) {
        cur->children[key[i]] = new Trie();
      }
      cur = cur->children[key[i]];
      if (i == key.length() - 1) {
        cur->is_end = true;
      }
    }
  }

  int AutoComplete(string &key) {
    int cnt = 1;
    Trie *cur = children[key[0]];
    for (size_t i = 1; i < key.length(); i++) {
      if (cur->children.size() > 1 || cur->is_end) {
        cnt++;
      }
      cur = cur->children[key[i]];
    }
    return cnt;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed;
  cout.precision(2);

  int N;

  vector<string> words;

  while (cin >> N) {
    words.clear();

    for (int i = 0; i < N; i++) {
      string word;
      cin >> word;
      words.push_back(word);
    }

    Trie root;
    for (string &word : words) {
      root.Insert(word);
    }

    int sum = 0;
    for (string &word : words) {
      sum += root.AutoComplete(word);
    }

    cout << (double)sum / N << '\n';
  }

  return 0;
}
