#include <iostream>

using namespace std;

static constexpr int kMaxNumNodes = 100'004;

int idx_inorder[kMaxNumNodes];
int inorder[kMaxNumNodes];
int postorder[kMaxNumNodes];
int num_nodes;

void findPreorder(const int in_start, const int in_end, const int post_start,
                  const int post_end) {
  if (in_start > in_end || post_start > post_end) {
    return;
  }

  const int root = postorder[post_end];

  cout << root << ' ';

  const int in_idx_root = idx_inorder[root];
  const int size_left_child = in_idx_root - in_start;
  const int size_right_child = in_end - in_idx_root;

  findPreorder(in_start, in_idx_root - 1, post_start,
               post_start + size_left_child - 1);
  findPreorder(in_idx_root + 1, in_end, post_end - size_right_child,
               post_end - 1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> num_nodes;

  for (int i = 1; i <= num_nodes; i++) {
    cin >> inorder[i];
    idx_inorder[inorder[i]] = i;
  }

  for (int i = 1; i <= num_nodes; i++) {
    cin >> postorder[i];
  }

  findPreorder(1, num_nodes, 1, num_nodes);

  return 0;
}
